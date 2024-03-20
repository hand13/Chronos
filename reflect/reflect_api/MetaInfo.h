#pragma once
#include <string>
#include <unordered_map>
struct MetaInfo{
    typedef std::unordered_map<std::string, std::string> AttrMap;
    /**
     * @brief 是否被宏标记
     * 
     */
    bool marked;
    AttrMap attrMap;
    MetaInfo():marked(false){}
};