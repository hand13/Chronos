#pragma once
#include <string>
#include "MetaPrefix.h"
class RefelctTest{
    CClass
    private:
    CField(id)
    int id;
    CField(password)
    std::string password;
    public:
    RefelctTest();
    CMethod(getNames)
    virtual int getNames(int id,std::string target);
    CMethod(getJob)
    virtual int getJob(int id);
    ~RefelctTest();
};