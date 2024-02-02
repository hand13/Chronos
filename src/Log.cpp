#include <codecvt>
#include <iostream>
#include "Log.h"
namespace Chronos {
    void Log(const std::wstring& msg,unsigned int level) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
        std::string out = conversion.to_bytes(msg);
        if(level == 0){
            std::cout<<out<<std::endl;
        }else {
            std::cerr<<out<<std::endl;
        }
    }
}