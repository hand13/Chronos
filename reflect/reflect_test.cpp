#include <string>
#include <iostream>
#include "reflect_api/Field.h"
#include "reflect_api/Metaspace.h"
#include "generated/load_all.h"
#include "head_for_reflect.h"
void test(){
    Metaspace ms;
    loadAll(&ms);
    ms.solveLink();
    Klass * tmp = ms.getKlass("ReflectTest");
    ReflectTest m;
    m.id = 12;
    for(auto f : tmp->fields){
        std::cout<<f.valueType.rawName<<std::endl;
        if(f.valueType.rawName == "i32" || f.valueType.rawName == "int"){
            int tmp = f.getValue<int>(&m);
            std::cout<<tmp<<std::endl;
        }
    }
}

int main(){
    test();
    return 0;
}