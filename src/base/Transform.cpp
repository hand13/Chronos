#include "Transform.h"
namespace Chronos {
    Transform::Transform(){
        pos = {0,0,0};
        scale = {1.f,1.f,1.f};
        rotation = {0,0,0};
    }
    Matrix4f Transform::getMatrix(){
        Matrix4f result;
        result <<
        scale.x,0.f,0.f,pos.x,
        0.f,scale.y,0.f,pos.y,
        0.f,0.f,scale.z,pos.z,
        0.f,0.f,0.f,1.f;
        return result;
    }
}