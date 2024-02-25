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

    typedef GenericParam<int> IntParam;
    typedef GenericParam<float> FloatParam;
    typedef GenericParam<Float2> Float2Param;
}