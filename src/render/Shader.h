#pragma once
#include <string>
#include "Param.h"
namespace Chronos {
    class Shader {
        public:
        virtual void setParam(const std::string& name,const Param& param) = 0;
        virtual void apply() = 0;
        virtual ~Shader(){}
    };
}