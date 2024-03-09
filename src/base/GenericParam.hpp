#pragma once
#include "Param.h"
namespace Chronos {
    template<typename T>
    class GenericParam:public Param{
        private:
        std::string name;
        PackInfo packInfo;
        public:
        virtual ParamSignature signature()const override{
            return ParamSignature(FetchType<T>()(),sizeof(T));
        }
        virtual void* asData()override{
            return &value;
        }
        virtual std::string getName()override{
            return name;
        }
        virtual PackInfo getPackInfo() override{
            return packInfo;
        }
        T value;
        GenericParam(const std::string& name,const T& value,PackInfo packInfo):name(name),value(value),packInfo(packInfo){
        }
        GenericParam(const std::string& name,PackInfo packInfo):name(name),packInfo(packInfo){}
        virtual ~GenericParam(){};
    };

    template<>
    class GenericParam<RawData>:public Param{
        private:
        std::string name;
        PackInfo packInfo;
        public:
        virtual ParamSignature signature()const override{
            return ParamSignature(FetchType<RawData>()(),value.getSize());
        }
        virtual void* asData()override{
            return value.getData();
        }
        virtual std::string getName()override{
            return name;
        }
        virtual PackInfo getPackInfo() override {
            return packInfo;
        }
        RawData value;
        GenericParam(const RawData& value,const std::string&name,PackInfo packInfo):name(name),packInfo(packInfo),value(value){
        }
        GenericParam(const std::string&name,size_t size,PackInfo packInfo):name(name),packInfo(packInfo),value(size){}
        virtual ~GenericParam(){};
    };

    typedef GenericParam<int> IntParam;
    typedef GenericParam<float> FloatParam;
    typedef GenericParam<Float2> Float2Param;
    typedef GenericParam<Float3> Float3Param;
    typedef GenericParam<Float4> Float4Param;
    typedef GenericParam<Matrix4f> Matrix4fParam;
    typedef GenericParam<RawData> RawDataParam;
    typedef GenericParam<SPTexture2D> Texture2DParam;
}