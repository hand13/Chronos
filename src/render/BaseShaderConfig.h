#pragma once
#include "ShaderConfig.h"
#include <map>
#include <string>
namespace Chronos {
    class BaseShaderConfig :public ShaderConfig{
        private:
        void constructParams();
        void destroyParams();
        protected:
        std::map<std::string,ParamType> paramList;
        std::string shaderName;
        ShaderType shaderType;
        std::map<std::string,Param*> params;
        virtual void initShaderInfoAndParamList() = 0;
        virtual void init();
        public:
        BaseShaderConfig();
        virtual bool checkParam(const std::string& paramName,const Param& param)const;
        virtual const Param* getParam(const std::string& name)const override;
        virtual const std::map<std::string, ParamType>& getParamList()const override;
        virtual void setParam(const std::string& name,const Param& param) override;
        virtual const std::string& getShaderName()const override;
        virtual ShaderType getShaderType()const override;
        virtual ~BaseShaderConfig();
    };
}