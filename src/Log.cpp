#include <codecvt>
#include <iostream>
#include "Log.h"
namespace Chronos {
    void Log(const std::wstring& msg) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
        std::string out = conversion.to_bytes(msg);
        std::cout<<out<<std::endl;
    }
}