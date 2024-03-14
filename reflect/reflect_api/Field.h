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

    template<typename T>
    T getValue(void * obj){
        return *reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj) + offset));
    }

    template<typename T>
    T& getRef(void * obj){
        return *reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj) + offset));
    }

    template<typename T>
    T* getPointer(void * obj){
        return reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj) + offset));
    }
};