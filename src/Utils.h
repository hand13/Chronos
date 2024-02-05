#pragma once
#include <string>
#include <vector>

struct SizeU{
    unsigned int width;
    unsigned int height;
    SizeU(){
        width = 0;
        height = 0;
    }
};

void Panic(const std::wstring& msg);
void Panic(const std::string& msg);
std::string WideToUTF8(const std::wstring& str);
std::vector<unsigned char> readDataFromFile(const char * fileName);