#include "BaseShaderConfig.h"

#include <vector>

#include "render/ShaderConfig.h"


namespace Chronos {

BaseShaderConfig::BaseShaderConfig(const std::string& shaderName,
                                   ShaderType shaderType)
    : shaderName(shaderName), shaderType(shaderType) {}

const std::string& BaseShaderConfig::getShaderName() const {
    return shaderName;
}

const std::vector<ConstantDataDef>& BaseShaderConfig::getConstantDataDef()
    const {
    return constantDataDef;
}

ShaderType BaseShaderConfig::getShaderType() const { return shaderType; }
void BaseShaderConfig::registerConstantDataDef(const ConstantDataDef& cdd) {
    constantDataDef.push_back(cdd);
}
BaseShaderConfig::~BaseShaderConfig() {}
}  // namespace Chronos