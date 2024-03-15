#pragma once
#include "Access.h"
#include <string>
#include <vector>
#include "MethodParam.h"
#include "MetaInfo.h"
/**
 * @brief 方法
 * 
 */
struct Method{
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
    MetaInfo metaInfo;
    /**
     * @brief 返回类型
     * 
     */
    ValueType returnType;
    /**
     * @brief 参数
     * 
     */
    std::vector<MethodParam> params;
    bool isVirtual = false;

};