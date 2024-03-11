#pragma once
#include <string>
#include <vector>
enum AccessInfo {
    PUBLIC,
    PROTECTED,
    PRIVATE,
};
struct MethodParamInfo {
    std::string name;
    std::string type;
};
struct FieldInfo {
    public:
    AccessInfo access;
    std::string name;
    std::string type;
};
struct ConstructorInfo{
    AccessInfo access;
    std::string name;
    std::vector<MethodParamInfo> params;
};
struct MethodInfo{
    AccessInfo access;
    std::string name;
    std::string returnType;
    std::vector<MethodParamInfo> params;
    bool isVirtual = false;
};
struct KlassInfo {
    std::string name;
    std::vector<FieldInfo> fileds;
    std::vector<MethodInfo> methods;
    std::vector<ConstructorInfo> contrustors;
};

std::string toString(const AccessInfo& a);
std::string toString(const MethodParamInfo& a);
std::string toString(const MethodInfo& a);
std::string toString(const FieldInfo& a);
std::string toString(const ConstructorInfo& a);
std::string toString(const KlassInfo& a);