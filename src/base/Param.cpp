#include "Param.h"

#include "GenericParam.hpp"
#include "Utils.h"

namespace Chronos {

Param* constructParamFromType(const std::string& name, ParamType type,
                              PackInfo packInfo, size_t size) {
    Param* result = nullptr;
#define CASE_NEW(X, Y, N, P)                \
    case (X): {                             \
        result = new GenericParam<Y>(N, P); \
        break;                              \
    }
    switch (type) {
        CASE_NEW(INT, int, name, packInfo)
        CASE_NEW(FLOAT, float, name, packInfo)
        CASE_NEW(FLOAT2, Float2, name, packInfo)
        CASE_NEW(FLOAT3, Float3, name, packInfo)
        CASE_NEW(FLOAT4, Float4, name, packInfo)
        CASE_NEW(MATRIX4F, Matrix4f, name, packInfo)
        CASE_NEW(SPTEXTURE2D, SPTexture2D, name, packInfo)
        case RAWDATA:
            result = new GenericParam<RawData>(name, size, packInfo);
            break;
        case NOTHING:
        default:
            Panic("should not be here");
    }
    return result;
#undef CASE_NEW
}
}  // namespace Chronos
