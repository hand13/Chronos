#pragma once
#include <base/Utils.h>

#include <memory>

#include "BaseShaderConfig.h"
#include "VertexProc.h"
#include "render/ShaderConfig.h"

namespace Chronos {
class PBRVertexProc : public VertexProc {
   private:
    std::unique_ptr<ShaderConfig> sc;

   public:
    struct PBRVertexConsData {
        Matrix4f modelMatrix;
        Matrix4f normalMatrix;
    };
    PBRVertexProc() {
        sc = std::make_unique<BaseShaderConfig>("pbr_vert", VERTEX_SHADER);
        sc->registerConstantDataDef(ConstantDataDef(
            "consData", CDT_ConstantBuffer, sizeof(PBRVertexConsData), 1));
    }
    virtual ShaderConfig* getShaderConfig() { return sc.get(); }
    virtual ~PBRVertexProc(){};
};
}  // namespace Chronos