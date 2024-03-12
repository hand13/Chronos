#pragma once
class Klass;
enum ValueTypeEnum {
    Value,
    Ref,
    Pointer
};

struct ValueType {
    ValueTypeEnum type;
    Klass* klass;
};