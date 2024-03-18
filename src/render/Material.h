#pragma once
#include "ShaderConfig.h"
#include "BaseRenderStateHolder.h"
namespace Chronos {
    class Material:public BaseRenderStateHolder{
        private:
        public:
        virtual ShaderConfig * getShaderConfig() = 0;
        virtual ~Material(){};
    };
}