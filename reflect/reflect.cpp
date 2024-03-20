#include "CodeGenerator.h"
#include <exception>
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <cxxopts.hpp>
using json = nlohmann::json;
namespace fs = std::filesystem;
static std::string readFileToString(const std::string file_path){
    std::ifstream is(file_path);
    std::ostringstream os;
    char tmp;
    while(os && is.get(tmp)){
        os.put(tmp);
    }
    return os.str();
}

static bool exists_file(const fs::path & path){
    fs::file_status fstatus = fs::status(path);
    return fs::exists(fstatus) && fs::is_regular_file(fstatus);
}
static bool exists_dir(const fs::path & path){
    fs::file_status fstatus = fs::status(path);
    return fs::exists(fstatus) && fs::is_directory(fstatus);
}
static cxxopts::Options buildOptions(){
    cxxopts::Options coptions("Reflect","reflect for Chronos Engine");
    coptions.add_options()
    ("h,help","print usage")
    ("f,file","reflect file name",cxxopts::value<std::string>()->default_value("reflect.json"))
    ("c,clean","delete all file in gen dir")
    ;
    return coptions;
}

static void clean(const char * dir){
    fs::path gen_path(dir);
    fs::directory_iterator di(gen_path);
    for(auto& f :di){
        if(f.is_regular_file()){
            fs::remove(f);
        }
    }
}

static long long getFileLastWriteTime(const fs::path& file){
    long long last_time = fs::last_write_time(file).time_since_epoch().count();
    return last_time;
}

static std::vector<std::string> filterWithTileStampAndCleanUnsedFiles(const std::string& src_dir
        ,const std::vector<std::string>& srcs,const json& jcache){
    std::vector<std::string> result;
    std::vector<std::string> unsed_files;
    for(auto & src:srcs){
        fs::path src_path(src_dir + "/" + src);
        if(!exists_file(src_path)){
            throw std::exception("no such file");
        }
        if(!jcache[src].is_null()){
            long long last_write_time = getFileLastWriteTime(src_path);
            long long time_in_cache = jcache[src]["time"];
            if(last_write_time > time_in_cache){
                result.push_back(src);
            }
        }else{
            result.push_back(src);
        }
    }

    for(auto & res :result){
        if(!jcache[res].is_null()){
            std::vector<std::string> gen_files = jcache[res]["gen_files"];
            for(auto& tmp:gen_files){
                unsed_files.push_back(tmp);
            }
        }
    }
    std::vector<std::string> generated_srcs = jcache["generated_srcs"];
    for(auto & generated_src :generated_srcs){
        bool find = false;
        for(auto & src : srcs){
            if(src == generated_src){
                find = true;
                break;
            }
        }
        if(!find){
            std::vector<std::string> gen_files = jcache[generated_src]["gen_files"];
            for(auto& tmp:gen_files){
                unsed_files.push_back(tmp);
            }
        }
    }

    for(auto & unsed : unsed_files){
        fs::path unsed_file(unsed);
        fs::remove(unsed_file);
        std::cout<<"remove outdated file "<<unsed<<std::endl;
    }

    return result;
}

static void genCache(json * json,const GenMap& gm){
}


int main(int argn,const char * args[]){
    auto opts = buildOptions();
    auto result = opts.parse(argn, args);

    if (result.count("help")) {
      std::cout << opts.help() << std::endl;
      return 0;
    }

    std::string configfile =  result["file"].as<std::string>();
    if(!exists_file(configfile)){
        std::cout<<"config file not found ,-f choose a file"<<std::endl;
        return -1;
    }

    fs::path configPath(configfile);
    std::string str = readFileToString("reflect.json");
    json jconfig;
    jconfig = json::parse(str);
    std::string src_dir = jconfig["src_dir"];
    std::vector<std::string> srcs = jconfig["srcs"];
    std::string gen_dir = jconfig["gen_dir"];
    std::string load_fn_name = jconfig["load_fn_name"];
    std::vector<std::string> include_dirs = jconfig["include_dirs"];

    if(!exists_dir(src_dir)){
        std::cerr<<"src_dir not found"<<std::endl;
        return -1;
    }
    if(!exists_dir(gen_dir)){
        std::cerr<<"gen_dir not found"<<std::endl;
        return -1;
    }
    for(auto str:srcs){
        std::string tmp = src_dir + "/" + str;
        if(!exists_file(tmp)){
            std::cerr<<str<<" not found"<<std::endl;
            return -1;
        }
    }

    if(result.count("clean")){
        clean(gen_dir.c_str());
        return 0;
    }

    CodeGenerator cg;

    std::string cache_file = gen_dir + "/" + ".cache";
    GenMap genMap;
    if(exists_file(cache_file)){
        json jcache = json::parse(readFileToString(cache_file));
        std::vector<std::string> srcs_need = filterWithTileStampAndCleanUnsedFiles(src_dir, srcs, jcache);
        genMap =  cg.generateCodeFromSrc(src_dir,srcs_need,gen_dir,load_fn_name,include_dirs);
    }else {
        genMap = cg.generateCodeFromSrc(src_dir,srcs,gen_dir,load_fn_name,include_dirs);
    }
    genCache(&jconfig,genMap);

    return 0;
}