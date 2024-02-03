#pragma once
namespace Chronos {
    class Shader {
        public:
        virtual void useShader()const = 0;
        virtual ~Shader(){}
    };
}