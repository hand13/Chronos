#pragma once
#include "Utils.h"
#define MakeFetchType(X,Y) template<> \
struct FetchType<X> {\
    constexpr ParamType operator()(){\
        return Y;\
    }\
};
namespace Chronos{
    enum ParamType {
        NOTHING,
        INT,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        MATRIX4F,
        RAWDATA
    };
    template<typename T>
    struct FetchType{
        constexpr ParamType operator()(){
            return NOTHING;
        }
    };
    MakeFetchType(int, INT);
    MakeFetchType(float, FLOAT)
    MakeFetchType(Float2,FLOAT2);
    MakeFetchType(Float3, FLOAT3);
    MakeFetchType(Float4, FLOAT4);
    MakeFetchType(Matrix4f, MATRIX4F);
    MakeFetchType(RawData,RAWDATA);

    struct ParamSignature{
        ParamSignature(ParamType type,size_t size):type(type),size(size){}
        ParamType type;
        size_t size;
        bool operator==(const ParamSignature& other)const{
            return type == other.type;
        }
    };

    class Param {
        public:
        virtual ParamSignature signature()const = 0;
        virtual void* asData() = 0;
        virtual std::string getName() = 0;
        virtual ~Param(){}
    };
    Param* constructParamFromType(const std::string& name,ParamType type,size_t rawDataSize = 0);

}