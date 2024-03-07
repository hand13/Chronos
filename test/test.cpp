#include "ParamList.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include "StringHelper.h"
void param_test(){
    const char * test = "hello world";
    Chronos::ParamList pl;
    pl.registerParam("id", Chronos::INT);
    pl.registerParam("pos",Chronos::FLOAT3);
    pl.registerParam("name", Chronos::RAWDATA,0,strlen(test)+1);
    pl.setParamValue("id", 12);
    pl.setParamValue("pos",Float3(12.f,2.f,2.f));

    RawData tmp((const unsigned char*)test,strlen(test)+1);
    pl.setParamValue("name",tmp);
    Chronos::Param * pm =  pl.getParam("name");
    std::cout<<(const char*)pm->asData()<<std::endl;
    RawData rd = pl.packDataInSlot(0);
    std::cout<<rd.getSize()<<std::endl;
}
void model_loader_test(){

}
int main() {
    param_test();
    model_loader_test();
    std::wstring md = UTF8toWide("你他妈在逗我");
    std::string off = WideToUTF8(md);
    std::cout<<off<<std::endl;
    return 0;
};