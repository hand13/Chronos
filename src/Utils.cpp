#include "Utils.h"
#include <chrono>
#include <cstdio>
#include <cstring>
#include <exception>
#include <iterator>
#include <string>
#include <vector>
#include <winerror.h>
#include "Log.h"
#include <codecvt>
#include <Poco/File.h>
using namespace std::chrono;

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
void Panic(const std::string& msg) {
    Chronos::Log(msg);
    throw std::exception(msg.c_str());
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
RawData::RawData(size_t size){
   data = new unsigned char[size];
   memset(data, 0, size);
   this->size = size;
}

RawData::RawData(const unsigned char * odata,size_t size){
    data = new unsigned char[size];
    this->size = size;
    memcpy(data, odata, size);
}
RawData::RawData(const RawData& other){
    RawData(other.data,other.size);
}

void RawData::operator=(const RawData& other){
    if(size != other.size){
        clean();
        data = new unsigned char[other.size];
        size = other.size;
    }
    memcpy(data, other.data, size);
}

RawData::RawData(RawData&& other){
    data = other.data;
    size = other.size;
    other.data = nullptr;
    other.size = 0;
}
void RawData::clean(){
    if(data){
        delete data;
    }
    size = 0;
}
unsigned char * RawData::getData(){
    return data;
}
size_t RawData::getSize()const{
    return size;
}

RawData::~RawData(){
    clean();
}

static long long epoch_time(){
    time_point<system_clock> now = system_clock::now();
    time_point<system_clock,milliseconds> ms = time_point_cast<milliseconds>(now);
    return ms.time_since_epoch().count();
}

void Timer::start(){
    lastEpochTime = epoch_time();
    startEpochTime = lastEpochTime;
}

long long Timer::elpasedTimeFromStart()const{
    return epochTime() - startEpochTime;
}

long long Timer::epochTime()const {
    return epoch_time();
}

unsigned int Timer::delta(){
    long long tmp = epoch_time();
    unsigned int delta = tmp - lastEpochTime;
    lastEpochTime = tmp;
    return delta;
}
