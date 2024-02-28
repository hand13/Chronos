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
    unsigned char * data;
    size_t size;
    void clean();
    public:
    RawData(size_t size);
    RawData(const unsigned char * data,size_t size);
    RawData(const RawData& other);
    RawData(RawData&& other);
    void operator=(const RawData& other);
    unsigned char * getData();
    size_t getSize()const;
    ~RawData();
};

class Timer {
    private:
    long long startEpochTime;
    long long lastEpochTime;//microsecond
    public:
    void start();
    long long epochTime()const;
    long long elpasedTimeFromStart()const;
    unsigned int delta();
};

typedef Eigen::Matrix4f Matrix4f ;

void Panic(const std::wstring& msg);
void Panic(const std::string& msg);
std::string WideToUTF8(const std::wstring& str);
std::vector<unsigned char> readDataFromFile(const char * fileName);