#pragma once
#include "Shader.h"
namespace Chronos {
    class VertexShader:public Shader{
        public:
        virtual void setParam(const std::string& name,const Param& param) = 0;
        virtual void apply() = 0;
        virtual ~VertexShader(){}
    };
}