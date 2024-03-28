#pragma once
#include "BaseRenderStateHolder.h"
#include "ShaderConfig.h"

namespace Chronos {
class VertexProc : public BaseRenderStateHolder {
   public:
    virtual ShaderConfig* getShaderConfig() = 0;
    virtual ~VertexProc(){};
};
}  // namespace Chronos