#include <cxxopts.hpp>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <sstream>
#include <string>
#include <vector>

#include "CodeGenerator.h"

using json = nlohmann::json;
namespace fs = std::filesystem;
static std::string readFileToString(const std::string file_path) {
    std::ifstream is(file_path);
    std::ostringstream os;
    char tmp;
    while (os && is.get(tmp)) {
        os.put(tmp);
    }
    return os.str();
}

static bool exists_file(const fs::path& path) {
    fs::file_status fstatus = fs::status(path);
    return fs::exists(fstatus) && fs::is_regular_file(fstatus);
}
static bool exists_dir(const fs::path& path) {
    fs::file_status fstatus = fs::status(path);
    return fs::exists(fstatus) && fs::is_directory(fstatus);
}
static cxxopts::Options buildOptions() {
    cxxopts::Options coptions("Reflect", "reflect for Chronos Engine");
    coptions.add_options()("h,help", "print usage")(
        "f,file", "reflect file name",
        cxxopts::value<std::string>()->default_value("reflect.json"))(
        "c,clean", "delete all file in gen dir");
    return coptions;
}

static void clean(const char* dir) {
    fs::path gen_path(dir);
    fs::directory_iterator di(gen_path);
    for (auto& f : di) {
        if (f.is_regular_file()) {
            fs::remove(f);
        }
    }
}

static long long getFileLastWriteTime(const fs::path& file) {
    long long last_time = fs::last_write_time(file).time_since_epoch().count();
    return last_time;
}
/**
 * @brief {
 * @return std::vector<std::string>
 */

static std::vector<std::string> filterWithTileStampAndCleanUnsedFiles(
    const std::string& src_dir, const std::vector<std::string>& srcs,
    const json& jcache) {
    std::vector<std::string> result;       // 改动与新增的文件
    std::vector<std::string> unsed_files;  // 不再需要的文件
    for (auto& src : srcs) {
        fs::path src_path(src_dir + "/" + src);
        if (!exists_file(src_path)) {
            throw std::exception("no such file");
        }
        if (jcache.find(src) != jcache.end()) {
            long long last_write_time = getFileLastWriteTime(src_path);
            long long time_in_cache = jcache[src]["time"];
            if (last_write_time > time_in_cache) {
                result.push_back(src);
            }
        } else {
            result.push_back(src);
        }
    }

    for (auto& res : result) {
        if (jcache.find(res) != jcache.end()) {
            std::vector<std::string> gen_files = jcache[res]["gen_files"];
            for (auto& tmp : gen_files) {
                unsed_files.push_back(tmp);
            }
        }
    }
    std::vector<std::string> generated_srcs = jcache["generated_srcs"];
    for (auto& generated_src : generated_srcs) {
        bool find = false;
        for (auto& src : srcs) {
            if (src == generated_src) {
                find = true;
                break;
            }
        }
        if (!find) {
            std::vector<std::string> gen_files =
                jcache[generated_src]["gen_files"];
            for (auto& tmp : gen_files) {
                unsed_files.push_back(tmp);
            }
        }
    }

    for (auto& unsed : unsed_files) {
        fs::path unsed_file(unsed);
        fs::remove(unsed_file);
        std::cout << "remove outdated file " << unsed << std::endl;
    }

    return result;
}

/**
 * @brief
    "generated_srcs":[
        "src_name"
        "src_name1"
    ],
    "src_name":{
        "time":32432432,
        "gen_files":[
            "tmp0.cpp","tmp1.cpp"
        ],
        generated_fns:[
            "load_xxx","load_xxx1"
        ]
        },
    "src_name1":{
        "time":32432432,
        "gen_files":[
            "tmp0.cpp","tmp1.cpp"
        ],
        generated_fns:[
            "load_xxx","load_xxx1"
        ]
        },
    }
 *
 * @param json
 * @param gm
 */
static std::pair<json, std::vector<std::string>> genJson(
    json* old_cache, const std::string& src_dir,
    const std::vector<std::string>& srcs, const GenMap& gm) {
    std::pair<json, std::vector<std::string>> res;

    json result;
    std::vector<std::string> fns;
    for (auto& src : srcs) {
        if (gm.find(src) != gm.end()) {
            result["generated_srcs"].push_back(src);
            const std::vector<GenDetail>& genMap = gm.at(src);
            result[src]["time"] = getFileLastWriteTime(src_dir + "/" + src);
            for (auto& gd : genMap) {
                result[src]["generated_fns"].push_back(gd.load_fn);
                result[src]["gen_files"].push_back(gd.gen_file_name);
                fns.push_back(gd.load_fn);
            }
        } else if (old_cache != nullptr &&
                   old_cache->find(src) != old_cache->end()) {
            result["generated_srcs"].push_back(src);
            json& tmp_cache = *old_cache;
            result[src] = tmp_cache[src];
            std::vector<std::string> tmp_fns = tmp_cache[src]["generated_fns"];
            for (auto& tmp_fn : tmp_fns) {
                fns.push_back(tmp_fn);
            }
        } else {
            throw std::exception("should not happended");
        }
    }
    res.first = result;
    res.second = fns;
    return res;
}

static void saveJsonFile(const json& j, const std::string& file_name) {
    std::ofstream os(file_name);
    std::string jstr = j.dump(4);
    os.write(jstr.c_str(), jstr.length());
}

int main(int argn, const char* args[]) {
    auto opts = buildOptions();
    auto result = opts.parse(argn, args);

    if (result.count("help")) {
        std::cout << opts.help() << std::endl;
        return 0;
    }

    std::string configfile = result["file"].as<std::string>();
    if (!exists_file(configfile)) {
        std::cout << "config file not found ,-f choose a file" << std::endl;
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

    if (!exists_dir(src_dir)) {
        std::cerr << "src_dir not found" << std::endl;
        return -1;
    }
    if (!exists_dir(gen_dir)) {
        std::cerr << "gen_dir not found" << std::endl;
        return -1;
    }
    for (auto str : srcs) {
        std::string tmp = src_dir + "/" + str;
        if (!exists_file(tmp)) {
            std::cerr << str << " not found" << std::endl;
            return -1;
        }
    }

    if (result.count("clean")) {
        clean(gen_dir.c_str());
        return 0;
    }

    CodeGenerator cg;

    std::string cache_file = gen_dir + "/" + ".cache.json";
    GenMap genMap;
    std::pair<json, std::vector<std::string>> gen_json_fns;
    if (srcs.size() == 0) {
        std::cout << "nothing to do" << std::endl;
    }
    if (exists_file(cache_file)) {
        json jcache = json::parse(readFileToString(cache_file));
        std::vector<std::string> srcs_need =
            filterWithTileStampAndCleanUnsedFiles(src_dir, srcs, jcache);
        if (srcs_need.size() == 0) {
            std::cout << "nothing update" << std::endl;
        }
        genMap =
            cg.generateCodeFromSrc(src_dir, srcs_need, gen_dir, include_dirs);
        gen_json_fns = genJson(&jcache, src_dir, srcs, genMap);
    } else {
        genMap = cg.generateCodeFromSrc(src_dir, srcs, gen_dir, include_dirs);
        gen_json_fns = genJson(nullptr, src_dir, srcs, genMap);
    }
    cg.generateAllLoadFun(gen_json_fns.second,
                          gen_dir + "/" + load_fn_name + ".h", load_fn_name);
    saveJsonFile(gen_json_fns.first, cache_file);
    return 0;
}