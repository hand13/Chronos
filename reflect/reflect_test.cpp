#include <cassert>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "generated/load_all.h"
#include "head_for_reflect.h"
#include "reflect_api/CallParam.h"
#include "reflect_api/Field.h"
#include "reflect_api/Klass.h"
#include "reflect_api/Metaspace.h"

using namespace nlohmann;
void test() {
    Metaspace ms;
    load_all(&ms);
    ms.solveLink();
    Klass* tmp = ms.getKlass("ReflectTest");
    ReflectTest m;
    m.id = 12;
    for (auto f : tmp->fields) {
        std::cout << f.valueType.rawName << std::endl;
        if (f.valueType.klass == ms.intclass() ||
            f.valueType.klass == ms.i32class()) {
            int wc = f.getValue<int>(&m);
            std::cout << wc << std::endl;
        }
    }
    Klass* ts = ms.getKlass<int>();
    std::cout << ts->size << std::endl;
    Klass* rk = ms.getKlass<ReflectTest>();
    assert(rk != nullptr);
    for (auto f : rk->fields) {
        std::cout << f.name << "type " << f.valueType.rawName << std::endl;
    }
    CallParams cps;
    ReflectTest* md = tmp->constructors[0].newInstance<ReflectTest>(cps);
    std::cout << "password " << md->getPassword() << "id " << md->getId()
              << std::endl;
}
namespace Testing {
class Parent {
   public:
    virtual ~Parent() {}
};
class Child : public Parent {
   public:
    virtual ~Child() {}
};
struct Md : public Parent {
   public:
    virtual ~Md() {}
};
}  // namespace Testing

void test1() {
    json ex3 = {{"test", true}, {"pi", 4.34}};
    ex3["md"] = {1, 2, 3, 4};
    std::string tmp = ex3.dump();
    std::ofstream os("test.json");
    os.write(tmp.c_str(), tmp.size());
}

int main() {
    // test();
    test1();
    return 0;
}