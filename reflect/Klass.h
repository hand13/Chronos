#pragma once
#include <string>
#include <vector>
#include "Constructor.h"
#include "Field.h"
#include "Method.h"


class Klass {
    public:
    std::string name;
    bool isPrimitiveType;
    size_t size;
    std::vector<Field> fields;
    std::vector<Method> methods;
    std::vector<Constructor> constructors;
    MetaInfo metaInfo;
    Klass(const std::string& name,bool isPrimitiveType,size_t size):name(name),isPrimitiveType(isPrimitiveType),size(size){}
};
