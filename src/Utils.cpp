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
