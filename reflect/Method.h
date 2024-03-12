#pragma once
#include "Access.h"
#include <string>
#include <vector>
#include "MethodParam.h"
#include "MetaInfo.h"
struct Method{
    Access access;
    std::string name;
    std::string returnType;
    MetaInfo metaInfo;
    Klass* returnTypeKlass;
    std::vector<MethodParam> params;
    bool isVirtual = false;

};