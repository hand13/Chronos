#pragma once
#include <string>
#include <vector>
#include "Constructor.h"
#include "Field.h"
#include "Method.h"


/**
 * @brief Class 元数据
 * 
 */
class Klass {
    public:
    /**
     * @brief Class 全名
     * 
     */
    std::string name;
    /**
     * @brief 是否为基本类型
     * 
     */
    bool isPrimitiveType;
    /**
     * @brief size
     * 
     */
    size_t size;
    /**
     * @brief 暂时仅有public field
     * 
     */
    std::vector<Field> fields;
    /**
     * @brief todo
     * 
     */
    std::vector<Method> methods;
    /**
     * @brief todo
     * 
     */
    std::vector<Constructor> constructors;
    /**
     * @brief class 相关的metainfo
     * 
     */
    MetaInfo metaInfo;
    Klass(const std::string& name,bool isPrimitiveType,size_t size):name(name),isPrimitiveType(isPrimitiveType),size(size){}

    template<typename T>
    T getValue(void * obj)const{
        return *reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj)));
    }

    template<typename T>
    T& getRef(void * obj)const{
        return *reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj)));
    }

    template<typename T>
    T* getPointer(void * obj)const{
        return reinterpret_cast<T*>((reinterpret_cast<unsigned char*>(obj)));
    }
};
