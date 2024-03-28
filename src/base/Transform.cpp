#include "Transform.h"

#include <base/Math.h>

#include "base/Utils.h"

namespace Chronos {
Transform::Transform() {
    pos = {0, 0, 0};
    scale = {1.f, 1.f, 1.f};
    rotation = {0, 0, 0};
}
Matrix4f Transform::getMatrix() {
    Matrix4f result;
    // clang-format off
    result <<
    scale.x,0.f,0.f,pos.x,
    0.f,scale.y,0.f,pos.y,
    0.f,0.f,scale.z,pos.z,
    0.f,0.f,0.f,1.f;
    float rx = degree2radian(rotation.x);
    float ry = degree2radian(rotation.y);
    float rz = degree2radian(rotation.z);
    Matrix4f rotationMatrixZ;
    rotationMatrixZ <<
    cos(rz),-sin(rz),0,0,
    sin(rz),cos(rz),0,0,
    0,0,1.f,0.f,
    0,0,0,1.f;
    Matrix4f rotationMatrixY;
    rotationMatrixY <<
    cos(ry),0,sin(ry),0,
    0,1.f,0,0,
    -sin(ry),0,cos(ry),0,
    0,0,0,1.f ;
    Matrix4f rotationMatrixX;
    rotationMatrixX <<
    1.f,0,0,0,
    0,cos(rx),-sin(rx),0,
    0,sin(rx),cos(rx),0,
    0,0,0,1.f
    ;
    // clang-format on
    Matrix4f rm = rotationMatrixZ * rotationMatrixY * rotationMatrixX;
    return result * rm;
}
}  // namespace Chronos