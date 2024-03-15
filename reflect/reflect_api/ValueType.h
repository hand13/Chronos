#pragma once
#include <string>
class Klass;
/**
 * @brief 类型
 * 
 */
enum ValueTypeEnum {
    Value,//值
    Ref,//引用
    Pointer//指针
};

struct ValueType {
    std::string rawName;
    std::string trueName;//todo
    ValueTypeEnum type;
    /**
     * @brief 解析后的class
     * 
     */
    Klass* klass;
};