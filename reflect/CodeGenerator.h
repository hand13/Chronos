#pragma once
#include <string>
#include <vector>
#include "KlassParser.h"
class CodeGenerator {

    private:
    KlassParser parser;
    std::string generateCodeFromKlass(const std::string& src_file,const std::string& target_path,const KlassInfo& klass);
    void generateAllLoadFun(const std::vector<std::string> fns,const std::string& file_name);
    public:
    void generateCodeFromSrc(const std::string &src_dir,const std::vector<std::string>& srcs,const std::string& target_dir);
    void generateCodeFromSrc(const std::string &src_dir,const std::vector<std::string>* srcs,const std::string& target_dir);
};