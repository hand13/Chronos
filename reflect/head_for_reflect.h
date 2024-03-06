#pragma once
#include "tmp.h"
#include <string>
#define TK
class Md{
    private:
    int names;
    std::string password;
    public:
    Md();
    TK
    virtual int getNames(int id,std::string target);
    virtual int getJob(int id);
    ~Md();
};
void test(){};

class Osk{
    private:
    int names;
    std::string password;
    public:
    Osk();
    TK
    virtual int getNames(int id,std::string target);
    virtual int getJob(int id);
    ~Osk();
};