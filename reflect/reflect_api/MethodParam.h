#pragma once
#include <string>

#include "ValueType.h"

/**
 * @brief 方法参数
 *
 */
struct MethodParam {
    /**
     * @brief 参数名称
     *
     */
    std::string name;
    /**
     * @brief 类型
     *
     */
    ValueType type;
};