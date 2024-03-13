#pragma once
#include "Access.h"
#include <string>
#include <vector>
#include "MethodParam.h"
#include "MetaInfo.h"
struct Method{
    Access access;
    std::string name;
    MetaInfo metaInfo;
    ValueType returnType;
    std::vector<MethodParam> params;
    bool isVirtual = false;

};