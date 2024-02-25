#include "../src/ParamList.h"
#include <iostream>
#include <string>
int main() {
    Chronos::ParamList pl;
    pl.registerParam("id", Chronos::INT);
    pl.registerParam("pos",Chronos::FLOAT3);
    pl.setParamValue("id", 12);
    pl.setParamValue("pos",Float3(12.f,2.f,2.f));
    Chronos::Param * mtp =pl.getParam("id");
    int * tmp = (int*)mtp->asData();
    std::cout<<*tmp<<std::endl;
    Chronos::Param * d = pl.getParam("pos");
    Float3* data = (Float3*)d->asData();
    std::cout<<data->x<<" "<<data->y<<" "<<data->z<<std::endl;
    return 0;
};