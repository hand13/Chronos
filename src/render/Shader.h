#pragma once
#include <string>
#include <map>
#include "../Param.h"
namespace Chronos {
    class Shader {
        public:
        virtual const Param& getParam(const std::string& name)const = 0;
        virtual const std::map<std::string, ParamType>& getParamList()const = 0;
        virtual void setParam(const std::string& name,const Param& param) = 0;
        virtual void apply() = 0;
        virtual ~Shader(){}
    };
}