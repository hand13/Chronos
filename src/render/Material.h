#pragma once
#include <string>
namespace Chronos {
    class Material{
        private:
        public:
        virtual void setParam(const std::string& param,int value) = 0;
        virtual void apply() = 0;
        virtual ~Material();
    };
}