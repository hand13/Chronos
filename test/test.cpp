#include "../src/GenericParam.hpp"
#include <iostream>
#include <string>
int main() {
    std::string test = "hello world";
    Chronos::GenericParam<RawData> rd;
    RawData tmp((unsigned char *)test.data(),test.size());
    rd.value = tmp;
    std::cout<<rd.signature().size<<" "<<rd.signature().type<<std::endl;
    return 0;
};