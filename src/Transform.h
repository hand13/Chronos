#pragma once
#include "Utils.h"
namespace Chronos {
    class Transform {
        public:
        Float3 pos;
        Float3 scale;
        Float3 rotation;
        Matrix4f getMatrix();
    };
}