#pragma once
#include "Types.h"
namespace Chronos{
    class Param {
        public:
        virtual Geometry::Type type() = 0;
        virtual ~Param(){}
    };
    class IntParam :public Param{
        public:
        virtual Geometry::Type type();
        int value;
        IntParam(int value);
        virtual ~IntParam(){};
    };
}