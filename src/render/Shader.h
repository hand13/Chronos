#pragma once
#include "Renderer.h"
namespace Chronos {
    class Shader {
        public:
        virtual void useIn(Renderer* renderer);
        virtual ~Shader(){}
    };
}