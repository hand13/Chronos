#include "Param.h"
#include "GenericParam.hpp"
#include "Utils.h"
namespace Chronos {

    Param* constructParamFromType(const std::string& name,ParamType type,size_t size){
        Param * result = nullptr;
        #define CASE_NEW(X,Y,N) case(X):{result = new GenericParam<Y>(N);break;}
        switch (type) {
            CASE_NEW(INT, int,name)
            CASE_NEW(FLOAT,float,name)
            CASE_NEW(FLOAT2, Float2,name)
            CASE_NEW(FLOAT3, Float3,name)
            CASE_NEW(FLOAT4, Float4,name)
            CASE_NEW(MATRIX4F, Matrix4f,name)
            case RAWDATA:
                result = new GenericParam<RawData>(name,size);
                break;
            NOTHING:
            default:
                Panic("should not be here");
        }
        return result;
        #undef CASE_NEW
    }
}
