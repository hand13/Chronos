#include "Utils.h"
#include <exception>
#include <string>
#include <winerror.h>
#include "Log.h"
#include <codecvt>

std::string WideToUTF8(const std::wstring& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conversion;
    std::string out = conversion.to_bytes(str);
    return out;
}
void Panic(const std::wstring& msg) {
    std::string tmp = WideToUTF8(msg);
    Chronos::Log(msg);
    throw std::exception(tmp.c_str());
}
