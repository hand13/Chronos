#pragma once
#include <memory>

#include "BaseShaderConfig.h"
#include "Material.h"

namespace Chronos {
class DefaultMaterial : public Material {
   private:
    std::unique_ptr<ShaderConfig> sc;

   public:
    DefaultMaterial() {
        sc = std::make_unique<BaseShaderConfig>("default_pixel", PIXEL_SHADER);
    }
    virtual ShaderConfig* getShaderConfig() { return sc.get(); }
    virtual ~DefaultMaterial(){};
};
}  // namespace Chronos