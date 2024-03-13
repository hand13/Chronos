#include "CodeGenerator.h"
#include <string>
#include "MetaInfoSolver.h"
#include <iostream>
#include <vcruntime_typeinfo.h>
#include <vector>
#include "reflect_api/Metaspace.h"
#include "reflect_bp.h"
void test(){
    std::string file_name = "d:/src/my/Chronos/reflect";
    std::string generate_dir = "d:/src/my/Chronos/reflect/generated";
    CodeGenerator cg;
    std::vector<std::string> files ={"head_for_reflect.h","tmp_test.h"};
    cg.generateCodeFromSrc(file_name,files, generate_dir);
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