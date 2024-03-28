#pragma once
#include "BaseRenderStateHolder.h"
#include "ShaderConfig.h"

namespace Chronos {
class Material : public BaseRenderStateHolder {
   private:
   public:
    virtual ShaderConfig* getShaderConfig() = 0;
    virtual ~Material(){};
};
}  // namespace Chronos