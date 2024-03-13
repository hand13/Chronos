#pragma once
#include <string>
class Klass;
enum ValueTypeEnum {
    Value,
    Ref,
    Pointer
};

struct ValueType {
    std::string rawName;
    std::string trueName;//
    ValueTypeEnum type;
    Klass* klass;
};