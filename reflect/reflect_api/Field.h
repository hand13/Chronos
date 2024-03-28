#pragma once
#include <string>

#include "Access.h"
#include "MetaInfo.h"
#include "ValueType.h"

/**
 * @brief 字段
 *
 */
struct Field {
   public:
    /**
     * @brief 访问权限
     *
     */
    Access access;
    /**
     * @brief 名称
     *
     */
    std::string name;
    /**
     * @brief metainfo
     *
     */
    MetaInfo metaInfo;
    /**
     * @brief 偏移
     *
     */
    size_t offset;
    /**
     * @brief 类型
     *
     */
    ValueType valueType;

    template <typename T>
    T getValue(void* obj) const {
        return *reinterpret_cast<T*>(
            (reinterpret_cast<unsigned char*>(obj) + offset));
    }

    template <typename T>
    T& getRef(void* obj) const {
        return *reinterpret_cast<T*>(
            (reinterpret_cast<unsigned char*>(obj) + offset));
    }

    template <typename T>
    T* getPointer(void* obj) const {
        return reinterpret_cast<T*>(
            (reinterpret_cast<unsigned char*>(obj) + offset));
    }
};