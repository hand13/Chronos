#pragma once
#include <string>
#include "reflect_api/MetaPrefix.h"
using namespace std;
typedef int i32;
class ReflectTest{
    CClass
    private:
    public:

    CField(id)
    i32 id;
    CField(password)
    string password;

    public:
    ReflectTest();

    CMethod(setId)
    void setId(i32 id);

    CMethod(getNames)
    virtual string getPassword();
    virtual i32 getId();

    virtual ~ReflectTest();
};