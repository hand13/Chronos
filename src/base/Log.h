#pragma once
#include <iostream>
#include <string>
namespace Chronos {
    inline void Log(const std::string& msg) {
        std::cout<<msg<<std::endl;
    }
    void Log(const std::wstring& msg,unsigned int level = 0);
}
