#pragma once
#include "Param.h"
namespace Chronos {
    template<typename T>
    class GenericParam:public Param{
        public:
        virtual ParamSignature signature()const override{
            return ParamSignature(FetchType<T>()(),sizeof(T));
        }
        virtual void* asData()override{
            return &value;
        }
        T value;
        GenericParam(const T& value):value(value){
        }
        GenericParam(){}
        virtual ~GenericParam(){};
    };

    template<>
    class GenericParam<RawData>:public Param{
        public:
        virtual ParamSignature signature()const override{
            return ParamSignature(FetchType<RawData>()(),value.getSize());
        }
        virtual void* asData()override{
            return value.getData();
        }
        RawData value;
        GenericParam(const RawData& value):value(value){
        }
        GenericParam(){}
        virtual ~GenericParam(){};
    };

    typedef GenericParam<int> IntParam;
    typedef GenericParam<float> FloatParam;
    typedef GenericParam<Float2> Float2Param;
    typedef GenericParam<Float3> Float3Param;
    typedef GenericParam<Float4> Float4Param;
    typedef GenericParam<Matrix4f> Matrix4fParam;
    typedef GenericParam<RawData> RawDataParam;
}