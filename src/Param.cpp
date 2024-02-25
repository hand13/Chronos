#include "Param.h"
#include "GenericParam.hpp"
#include "Utils.h"
namespace Chronos {

    Param* constructParamFromType(ParamType type){
        Param * result = nullptr;
        #define CASE_NEW(X,Y) case(X):{result = new GenericParam<Y>();break;}
        switch (type) {
            CASE_NEW(INT, int)
            CASE_NEW(FLOAT,float)
            CASE_NEW(FLOAT2, Float2)
            CASE_NEW(FLOAT3, Float3)
            CASE_NEW(FLOAT4, Float4)
            CASE_NEW(MATRIX4F, Matrix4f)
            NOTHING:
            default:
                Panic("should not be here");
        }
        return result;
    }
    void copyValue(Param& target,const Param& source){
        if(target.signature() != source.signature()) {
            Panic("Fatal Param Copy");
        }
    }
}
