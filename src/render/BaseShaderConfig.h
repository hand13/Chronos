#pragma once
#include "ShaderConfig.h"
#include <string>
namespace Chronos {
    class BaseShaderConfig :public ShaderConfig{
        private:
        ParamList pl;
        protected:
        std::string shaderName;
        ShaderType shaderType;
        public:
        BaseShaderConfig(const std::string &shaderName,ShaderType shaderType);
        virtual ParamList& getParamList() override;
        virtual const std::string& getShaderName()const override;
        virtual ShaderType getShaderType()const override;
        virtual ~BaseShaderConfig();
    };
}