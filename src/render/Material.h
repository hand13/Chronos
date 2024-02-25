#pragma once
#include <string>
#include "../Param.h"
namespace Chronos {
    class Material{
        private:
        public:
        virtual void setParam(const std::string& paramName,const Param& param) = 0;
        virtual void apply() = 0;
        virtual ~Material();
    };
}