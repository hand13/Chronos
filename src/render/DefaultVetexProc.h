#pragma once
#include <memory>

#include "BaseShaderConfig.h"
#include "VertexProc.h"
#include "base/Utils.h"
#include "render/ShaderConfig.h"

namespace Chronos {
class DefaultVertexProc : public VertexProc {
   private:
    std::unique_ptr<ShaderConfig> sc;

   public:
    DefaultVertexProc() {
        sc = std::make_unique<BaseShaderConfig>("default_vert", VERTEX_SHADER);
        sc->registerConstantDataDef(ConstantDataDef(
            "model_matrix", CDT_ConstantBuffer, sizeof(Matrix4f), 1));
    }
    virtual ShaderConfig* getShaderConfig() override { return sc.get(); }
    virtual ~DefaultVertexProc(){};
};
}  // namespace Chronos