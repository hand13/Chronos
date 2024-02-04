#include "Utils.h"
#include <cstdio>
#include <exception>
#include <iterator>
#include <string>
#include <vector>
#include <winerror.h>
#include "Log.h"
#include <codecvt>
#include <Poco/File.h>

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
std::vector<unsigned char> readDataFromFile(const char * fileName){
    Poco::File pf(fileName);
    if(!pf.exists()){
        Panic(L"未知文件");
    }
    std::vector<unsigned char> result;
    FILE* file = std::fopen(fileName,"rb");
    if(file == nullptr){
        Panic(L"fatal");
    }
    unsigned char buffer[1024];
    size_t s = 0;
    while((s=fread(buffer, sizeof(unsigned char),1024,file))>0) {
        result.insert(result.end(),std::begin(buffer),std::begin(buffer) + s);
    }
    fclose(file);
    file = nullptr;
    return result;
}
