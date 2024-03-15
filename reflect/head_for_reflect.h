#pragma once
#include <string>
#include "reflect_api/MetaPrefix.h"
typedef int i32;
class ReflectTest{
    CClass
    private:
    public:

    CField(id)
    i32 id;
    CField(password)
    std::string password;

    public:
    ReflectTest();

    CMethod(setId)
    void setId(i32 id);

    CMethod(getNames)
    virtual std::string getPassword();
    virtual i32 getId();

    virtual ~ReflectTest();
};