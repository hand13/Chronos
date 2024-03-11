#pragma once
#include <string>
#include <vector>
enum Access {
    PUBLIC,
    PROTECTED,
    PRIVATE,
};
struct MethodParam {
    std::string name;
    std::string type;
};
struct Field {
    public:
    Access access;
    std::string name;
    std::string type;
};
struct Constructor{
    Access access;
    std::string name;
    std::vector<MethodParam> params;
};
struct Method{
    Access access;
    std::string name;
    std::string returnType;
    std::vector<MethodParam> params;
    bool isVirtual = false;
};
struct Klass {
    std::string name;
    std::vector<Field> fileds;
    std::vector<Method> methods;
    std::vector<Constructor> contrustors;
};

std::string toString(const Access& a);
std::string toString(const MethodParam& a);
std::string toString(const Method& a);
std::string toString(const Field& a);
std::string toString(const Constructor& a);
std::string toString(const Klass& a);