#pragma once
#include "ShaderConfig.h"
namespace Chronos {
    class VertexProc{
        private:
        public:
        virtual ShaderConfig * getShaderConfig() = 0;
        virtual ~VertexProc(){};
    };
}