#include "CodeGenerator.h"
#include <string>
#include "MetaInfoSolver.h"
#include <iostream>
#include <vcruntime_typeinfo.h>
#include "Metaspace.h"
#include "reflect_bp.h"
void test(){
    std::string file_name = "head_for_reflect.h";
    std::string generate_dir = "d:/src/my/Chronos/reflect/generated";
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

}
void test1(){
    Metaspace ms;
    ms.load(load_reflect_test);
    Klass* rek = ms.getKlass("ReflectTest");
    for(auto f :rek->fields){
        std::cout<<f.offset<<std::endl;
    }
}

int main(){
    test();
    return 0;
}