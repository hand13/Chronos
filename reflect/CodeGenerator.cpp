#include "CodeGenerator.h"
#include <iostream>

void CodeGenerator::generateCodeFromSrc(const std::string &src_path,const std::string& target_dir){
    ParseContext pc;
    parser.parseFileIntoParseContext(src_path, pc);
    for(auto klass : pc.klasses){
        generateCodeFromKlass(target_dir+"/"+klass.name+"_generated.h",klass);
    }
}
void CodeGenerator::generateCodeFromKlass(const std::string& target_path,const Klass& klass){
    //todo
    std::cout<<"generated "<<klass.name<<std::endl;
}