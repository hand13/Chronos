#pragma once
#include <string>
#include <vector>
#include<map>
#include "KlassParser.h"


struct GenDetail{
    std::string gen_file_name;
    std::string load_fn;
    GenDetail(const std::string&gen_file_name,const std::string & load_fn):gen_file_name(gen_file_name),load_fn(load_fn){}
};

typedef std::map<std::string,std::vector<GenDetail>> GenMap;

class CodeGenerator {

    private:
    KlassParser parser;
    std::string generateCodeFromKlass(const std::string& src_file,const std::string& target_path,const KlassInfo& klass);
    public:
    GenMap generateCodeFromSrc(const std::string &src_dir,const std::vector<std::string>& srcs
    ,const std::string& target_dir,const std::vector<std::string>& include_dirs);
    void generateAllLoadFun(const std::vector<std::string> fns,const std::string& file_name,const std::string& load_fn_name);
};