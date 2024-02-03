#pragma once
#include <string>
#include <vector>
void Panic(const std::wstring& msg);
std::string WideToUTF8(const std::wstring& str);
std::vector<unsigned char> readDataFromFile(const char * fileName);