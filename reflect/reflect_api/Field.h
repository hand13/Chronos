#pragma once
#include "Access.h"
#include <string>
#include "MetaInfo.h"
#include "ValueType.h"
struct Field {
    public:
    Access access;
    std::string name;
    MetaInfo metaInfo;
    size_t offset;
    ValueType valueType;
};