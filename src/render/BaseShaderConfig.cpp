#include "BaseShaderConfig.h"
#include "../Utils.h"

namespace Chronos{

    BaseShaderConfig::BaseShaderConfig(){
        init();
    }
    void BaseShaderConfig::init(){
        initShaderInfoAndParamList();
        constructParams();
    }

    void BaseShaderConfig::constructParams(){

    }

    bool BaseShaderConfig::checkParam(const std::string& paramName,const Param& param)const{
        return false;
    }

    const Param* BaseShaderConfig::getParam(const std::string& name)const{
        return nullptr;
    }

    void BaseShaderConfig::setParam(const std::string& name,const Param& param) {
        if(!checkParam(name, param)){
            Panic("illegal param");
        }
    }
    const std::map<std::string, ParamType>& BaseShaderConfig::getParamList()const {
        return paramList;
    }
    const std::string& BaseShaderConfig::getShaderName()const {
        return shaderName;
    }

    ShaderType BaseShaderConfig::getShaderType()const {
        return shaderType;
    }
    void BaseShaderConfig::destroyParams(){
    }
    BaseShaderConfig::~BaseShaderConfig(){
        destroyParams();
    }
}