#pragma once
#include <memory>
#include <string>
#include <vector>
enum AccessInfo {
    PUBLIC,
    PROTECTED,
    PRIVATE,
};

struct Info {
    virtual ~Info() {}
};

struct MethodParamInfo : public Info {
    std::string name;
    std::string type;
    virtual ~MethodParamInfo() {}
};
struct FieldInfo : public Info {
   public:
    AccessInfo access;
    std::string name;
    std::string type;
    virtual ~FieldInfo() {}
};
struct ConstructorInfo : public Info {
    AccessInfo access;
    std::string name;
    std::vector<std::shared_ptr<MethodParamInfo>> params;
    virtual ~ConstructorInfo() {}
};
struct MethodInfo : public Info {
    AccessInfo access;
    std::string name;
    std::string returnType;
    std::vector<std::shared_ptr<MethodParamInfo>> params;
    bool isVirtual = false;
    virtual ~MethodInfo() {}
};
struct KlassInfo : public Info {
    std::string name;
    std::vector<std::shared_ptr<FieldInfo>> fileds;
    std::vector<std::shared_ptr<::MethodInfo>> methods;
    std::vector<std::shared_ptr<ConstructorInfo>> contrustors;
    virtual ~KlassInfo() {}
};

std::string toString(const AccessInfo& a);
std::string toString(const MethodParamInfo& a);
std::string toString(const MethodInfo& a);
std::string toString(const FieldInfo& a);
std::string toString(const ConstructorInfo& a);
std::string toString(const KlassInfo& a);