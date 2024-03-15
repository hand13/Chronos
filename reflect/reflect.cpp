#include "CodeGenerator.h"
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
    ;
    return coptions;
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
            break;
        }
    }

    CodeGenerator cg;
    cg.generateCodeFromSrc(src_dir,srcs,gen_dir,load_fn_name,include_dirs);
    return 0;
}