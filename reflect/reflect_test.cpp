#include <cassert>
#include <iostream>
#include "reflect_api/CallParam.h"
#include "reflect_api/Field.h"
#include "reflect_api/Klass.h"
#include "reflect_api/Metaspace.h"
#include "generated/load_all.h"
#include "head_for_reflect.h"
void test(){
    Metaspace ms;
    load_all(&ms);
    ms.solveLink();
    Klass * tmp = ms.getKlass("ReflectTest");
    ReflectTest m;
    m.id = 12;
    for(auto f : tmp->fields){
        std::cout<<f.valueType.rawName<<std::endl;
        if(f.valueType.klass == ms.intclass() || f.valueType.klass == ms.i32class()){
            int wc= f.getValue<int>(&m);
            std::cout<<wc<<std::endl;
        }
    }
    Klass * ts= ms.getKlass<int>();
    std::cout<<ts->size<<std::endl;
    Klass * rk = ms.getKlass<ReflectTest>();
    assert(rk != nullptr);
    for(auto f : rk->fields){
        std::cout<<f.name<<"type "<<f.valueType.rawName<<std::endl;
    }
    CallParams cps;
    ReflectTest * md = tmp->constructors[0].newInstance<ReflectTest>(cps);
    std::cout<<"password "<<md->getPassword()<<"id "<<md->getId()<<std::endl;
}
namespace Testing {
    class Parent {
        public:
        virtual ~Parent(){}
    };
    class Child:public Parent{
        public:
        virtual ~Child(){}
    };
    struct Md : public Parent{
        public:
        virtual ~Md(){}
    };
}

int main(){

    test();
    Testing::Parent * m =new Testing::Child;
    std::cout<<typeid(*m).name()<<std::endl;

    Testing::Parent * md =new Testing::Md;
    std::cout<<typeid(*md).name()<<std::endl;

    return 0;
}