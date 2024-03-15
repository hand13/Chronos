#pragma once
#include "Access.h"
#include <string>
#include <vector>
#include "MethodParam.h"
#include "MetaInfo.h"

/**
 * @brief 构造器
 * 
 */
struct Constructor{
    Access access;
    std::string name;
    MetaInfo metaInfo;
    /**
     * @brief 参数
     * 
     */
    std::vector<MethodParam> params;
};