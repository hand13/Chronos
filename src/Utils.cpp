#include "Utils.h"
#include <cstdio>
#include <cstring>
#include <exception>
#include <iterator>
#include <string>
#include <unicode/ucnv_err.h>
#include <unicode/umachine.h>
#include <unicode/urename.h>
#include <unicode/utypes.h>
#include <vector>
#include <winerror.h>
#include "Log.h"
#include <Poco/File.h>
#include "StringHelper.h"
void Panic(const std::wstring& msg) {
    std::string tmp = WideToUTF8(msg);
    Chronos::Log(msg);
    throw std::exception(tmp.c_str());
}
void Panic(const std::string& msg) {
    Chronos::Log(msg);
    throw std::exception(msg.c_str());
}

std::vector<u8> readDataFromFile(const char * fileName){
    Poco::File pf(fileName);
    if(!pf.exists()){
        Panic(L"未知文件");
    }
    std::vector<u8> result;
    FILE* file = std::fopen(fileName,"rb");
    if(file == nullptr){
        Panic(L"fatal");
    }
    u8 buffer[1024];
    size_t s = 0;
    while((s=fread(buffer, sizeof(u8),1024,file))>0) {
        result.insert(result.end(),std::begin(buffer),std::begin(buffer) + s);
    }
    fclose(file);
    file = nullptr;
    return result;
}
RawData::RawData(size_t size){
   data = new u8[size];
   memset(data, 0, size);
   this->size = size;
}

RawData::RawData(const u8 * odata,size_t size){
    data = new u8[size];
    this->size = size;
    memcpy(data, odata, size);
}
RawData::RawData(const RawData& other){
    RawData(other.data,other.size);
}

void RawData::operator=(const RawData& other){
    if(size != other.size){
        clean();
        data = new u8[other.size];
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
u8 * RawData::getData(){
    return data;
}
size_t RawData::getSize()const{
    return size;
}

void RawData::copyIntoThis(const u8* from,size_t from_start,size_t this_start,size_t size){
    memcpy(data+this_start, from + from_start, size);
}

RawData::~RawData(){
    clean();
}
