#pragma once
namespace Chronos{
    enum ParamType {
        INT,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
        MATRIX4F4,
        BUFFER
    };
    class Param {
        public:
        virtual ParamType type() = 0;
        virtual ~Param(){}
    };
    class IntParam :public Param{
        public:
        virtual ParamType type();
        int value;
        IntParam(int value);
        virtual ~IntParam(){};
    };
}