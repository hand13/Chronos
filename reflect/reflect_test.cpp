#include "CodeGenerator.h"
#include <string>
#include "MetaInfoSolver.h"
#include <iostream>
int main(){
    std::string file_name = "head_for_reflect.h";
    std::string generate_dir = "generated";
    CodeGenerator cg;
    cg.generateCodeFromSrc(file_name, generate_dir);
    std::string gs[]={
        "generated_class_","ghs","generated_class_ghs",
        "generated_field_","fhs","generated_field_fgs",
        "generated_method_","mhs","generated_method_mhs"
    };
    for(auto  s : gs){
        MetaInfoHelper mh = MetaInfoSolver::solveFieldName(s);
        if(mh.isMacro){
            std::cout<<mh.memberType<<mh.markedName<<std::endl;
        }
    }
    return 0;
}