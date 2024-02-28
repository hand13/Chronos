#include "Transform.h"
#include <d3d10.h>
namespace Chronos {
    Matrix4f Transform::getMatrix(){
        Matrix4f result;
        result <<
        1.f,0.f,0.f,pos.x,
        0.f,1.f,0.f,pos.y,
        0.f,0.f,1.f,pos.z,
        0.f,0.f,0.f,1.f;
        return result;
    }
}