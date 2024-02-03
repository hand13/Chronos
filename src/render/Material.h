#pragma once
#include <string>
#include "Shader.h"
namespace Chronos {
    class Material{
        private:
        public:
        virtual const Shader* getShader()const = 0;
        virtual void setParam(const std::string& param,int value) = 0;
        virtual void apply() = 0;
        virtual ~Material();
    };
}