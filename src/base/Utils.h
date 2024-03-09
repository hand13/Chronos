#pragma once
#include <string>
#include <vector>
#include <Eigen/Eigen>
#include "BaseTypes.h"

struct SizeU{
    u32 width;
    u32 height;
    SizeU(){
        width = 0;
        height = 0;
    }
};

struct Float2{
    float x;
    float y;
    Float2(float x,float y):x(x),y(y){}
    Float2(){
        x = 0;
        y = 0;
    }
};
struct Float3 {
    float x;
    float y;
    float z;
    Float3(float x,float y,float z):x(x),y(y),z(z){}
    Float3() {
        x = 0;
        y = 0;
        z = 0;
    }
};

struct Float4 {
    float x;
    float y;
    float z;
    float w;
    Float4(float x,float y,float z,float w):x(x),y(y),z(z),w(w){}
    Float4(){
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }
};

class RawData{
    private:
    u8 * data;
    size_t size;
    void clean();
    public:
    RawData(size_t size);
    RawData(const u8 * data,size_t size);
    RawData(const RawData& other);
    RawData(RawData&& other);
    void operator=(const RawData& other);
    u8 * getData();
    size_t getSize()const;
    void copyIntoThis(const u8* from,size_t from_start,size_t this_start,size_t size);
    ~RawData();
};


typedef Eigen::Matrix4f Matrix4f ;

void Panic(const std::wstring& msg);
void Panic(const std::string& msg);
std::vector<u8> readDataFromFile(const char * fileName);