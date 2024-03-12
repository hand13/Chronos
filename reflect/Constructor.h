#pragma once
#include "Access.h"
#include <string>
#include <vector>
#include "MethodParam.h"
#include "MetaInfo.h"

struct Constructor{
    Access access;
    std::string name;
    MetaInfo metaInfo;
    std::vector<MethodParam> params;
};