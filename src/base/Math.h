#pragma once
#define F_PI 3.1415926f
#define PI = 3.1415926
namespace Chronos{
    inline float degree2radian(float degree){
        return degree/360.f * 2.f * F_PI;
    }
    inline float radian2degree(float radian){
        return radian/(2.f *F_PI) * 360.f;
    }
}