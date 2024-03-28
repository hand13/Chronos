#pragma once
#include <string>

#include "reflect_api/MetaPrefix.h"

typedef int i32;
struct Test2 {
    int wc;
};
class ReflectTest {
    CClass private : public :

        CField(id) i32 id;
    CField(password) std::string password;

   public:
    ReflectTest();

    CMethod(setId) void setId(i32 id);

    CMethod(getNames) virtual std::string getPassword();
    virtual i32 getId();

    virtual ~ReflectTest();
};