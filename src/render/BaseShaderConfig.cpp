#include "BaseShaderConfig.h"

namespace Chronos{

    BaseShaderConfig::BaseShaderConfig(const std::string &shaderName,ShaderType shaderType):shaderName(shaderName),shaderType(shaderType){
    }

    const std::string& BaseShaderConfig::getShaderName()const {
        return shaderName;
    }

    ParamList& BaseShaderConfig::getParamList(){
        return pl;
    }

    ShaderType BaseShaderConfig::getShaderType()const {
        return shaderType;
    }
    BaseShaderConfig::~BaseShaderConfig(){
    }
}