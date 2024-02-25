#pragma once
#include "../Param.h"
#include <map>
#include <string>
#include "Types.h"
namespace Chronos{
    class ShaderConfig {
        public:
        virtual const Param* getParam(const std::string& name)const = 0;
        virtual const std::map<std::string, ParamType>& getParamList()const = 0;
        virtual void setParam(const std::string& name,const Param& param) = 0;
        virtual const std::string& getShaderName()const = 0;
        virtual ShaderType getShaderType()const = 0;
        virtual ~ShaderConfig(){}
    };
}