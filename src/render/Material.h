#pragma once
#include "ShaderConfig.h"
namespace Chronos {
    class Material{
        private:
        public:
        virtual ShaderConfig * getShaderConfig() = 0;
        virtual ~Material(){};
    };
}