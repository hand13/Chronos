#include "../src/ParamList.h"
#include <iostream>
#include <string>
void param_test(){
    const char * test = "hello world";
    Chronos::ParamList pl;
    pl.registerParam("id", Chronos::INT);
    pl.registerParam("pos",Chronos::FLOAT3);
    pl.registerParam("name", Chronos::RAWDATA,strlen(test)+1);
    pl.setParamValue("id", 12);
    pl.setParamValue("pos",Float3(12.f,2.f,2.f));

    RawData tmp((const unsigned char*)test,strlen(test)+1);
    pl.setParamValue("name",tmp);
    Chronos::Param * pm =  pl.getParam("name");
    std::cout<<(const char*)pm->asData()<<std::endl;
}
void model_loader_test(){

}
int main() {
    param_test();
    model_loader_test();
    return 0;
};