#pragma once
#include <string>
#include <vector>
#include <Eigen/Eigen>

struct SizeU{
    unsigned int width;
    unsigned int height;
    SizeU(){
        width = 0;
        height = 0;
    }
};

struct Float2{
    float x;
    float y;
};
struct Float3 {
    float x;
    float y;
    float z;
};

struct Float4 {
    float x;
    float y;
    float z;
    float w;
};

typedef  Eigen::Matrix4f Matrix4f;

void Panic(const std::wstring& msg);
void Panic(const std::string& msg);
std::string WideToUTF8(const std::wstring& str);
std::vector<unsigned char> readDataFromFile(const char * fileName);