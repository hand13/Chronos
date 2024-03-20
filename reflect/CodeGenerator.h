#pragma once
#include <string>
#include <vector>
#include<map>
#include "KlassParser.h"

typedef std::map<std::string,std::vector<std::string>> GenMap;
class CodeGenerator {

    private:
    KlassParser parser;
    std::string generateCodeFromKlass(const std::string& src_file,const std::string& target_path,const KlassInfo& klass);
    void generateAllLoadFun(const std::vector<std::string> fns,const std::string& file_name,const std::string& load_fn_name);
    public:
    GenMap generateCodeFromSrc(const std::string &src_dir,const std::vector<std::string>& srcs
    ,const std::string& target_dir,const std::string& load_fn_name,const std::vector<std::string>& include_dirs);
};