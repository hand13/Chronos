#pragma once
#include <base/ParamList.h>
#include <string>
#include "Types.h"
namespace Chronos{
    class ShaderConfig {
        public:
        virtual ParamList& getParamList() = 0;
        virtual const std::string& getShaderName()const = 0;
        virtual ShaderType getShaderType()const = 0;
        virtual ~ShaderConfig(){}
    };
}