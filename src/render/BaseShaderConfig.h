#pragma once
#include <string>
#include <vector>

#include "ShaderConfig.h"

namespace Chronos {
class BaseShaderConfig : public ShaderConfig {
   protected:
    std::vector<ConstantDataDef> constantDataDef;
    std::string shaderName;
    ShaderType shaderType;

   public:
    BaseShaderConfig(const std::string& shaderName, ShaderType shaderType);
    virtual const std::vector<ConstantDataDef>& getConstantDataDef()
        const override;
    virtual const std::string& getShaderName() const override;
    virtual ShaderType getShaderType() const override;
    void registerConstantDataDef(const ConstantDataDef& cdd) override;
    virtual ~BaseShaderConfig();
};
}  // namespace Chronos