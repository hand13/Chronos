#pragma once
#include <string>
std::string WideToUTF8(const std::wstring& str);
std::wstring UTF8toWide(const std::string& str);