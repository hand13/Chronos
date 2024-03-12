#pragma once
#include <string>
#include "ValueType.h"
struct MethodParam {
    std::string name;
    std::string typeName;
    ValueType type;
};