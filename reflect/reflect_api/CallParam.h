#pragma once
#include <vector>

class Klass;
struct CallParam{
    void * param;
    Klass * klass;
};
typedef std::vector<CallParam> CallParams;
typedef void * (*FunCall)(CallParams& params);
typedef void * (*MethodCall)(void * thiz,CallParams& params);