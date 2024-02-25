#include "../src/GenericParam.hpp"
#include <iostream>
int main() {
    Chronos::Float2Param * param = (Chronos::Float2Param*)Chronos::constructParamFromType(Chronos::FLOAT2);
    std::cout<<param->signature().size<<std::endl;
    param->value.x = 2;
    param->value.y = 2;
    Float2 data = param->value;
    std::cout<<data.x<<" "<<data.y<<std::endl;
    delete param;
    return 0;
};