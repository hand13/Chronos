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
    std::vector<Field> fileds;
    std::vector<Method> methods;
    std::vector<Constructor> constructors;
    MetaInfo metaInfo;
    Klass(const std::string& name,bool isPrimitiveType,size_t size):name(name),isPrimitiveType(isPrimitiveType),size(size){}


    static Klass boolKlass;

    static Klass i8Klass;
    static Klass i16Klass;
    static Klass i32Klass;
    static Klass i64Klass;

    static Klass u8Klass;
    static Klass u16Klass;
    static Klass u32Klass;
    static Klass u64Klass;
    static Klass f32Klass;
    static Klass f64Klass;
};
