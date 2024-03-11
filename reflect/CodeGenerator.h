#pragma once
#include <string>
#include "KlassParser.h"
class CodeGenerator {

    private:
    KlassParser parser;
    public:
    void generateCodeFromSrc(const std::string &src_path,const std::string& target_dir);
    void generateCodeFromKlass(const std::string& target_path,const KlassInfo& klass);

};