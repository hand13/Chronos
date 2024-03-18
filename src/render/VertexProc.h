#pragma once
#include "ShaderConfig.h"
#include "BaseRenderStateHolder.h"
namespace Chronos {
    class VertexProc:public BaseRenderStateHolder{
        public:
        virtual ShaderConfig * getShaderConfig() = 0;
        virtual ~VertexProc(){};
    };
}