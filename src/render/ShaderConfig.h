#pragma once
#include <base/ParamList.h>
#include <string>
#include "Types.h"
#include <base/BaseTypes.h>
#include <vector>
namespace Chronos{
    enum ConstantDataType {
        CDT_ConstantBuffer,
        CDT_Texture2D
    };
    struct ConstantDataDef {
        std::string name;
        ConstantDataType type;
        size_t size;
        u8 slot;
        ConstantDataDef(const std::string &name,ConstantDataType type,size_t size,u8 slot):name(name),type(type),size(size),slot(slot){}
    };
    class ShaderConfig {
        public:
        virtual const std::vector<ConstantDataDef>& getConstantDataDef()const = 0;
        virtual const std::string& getShaderName()const = 0;
        virtual ShaderType getShaderType()const = 0;
        virtual void registerConstantDataDef(const ConstantDataDef& cdd) = 0;
        virtual ~ShaderConfig(){}
    };
}