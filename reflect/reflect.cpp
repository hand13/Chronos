#include "CodeGenerator.h"
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>
using json = nlohmann::json;
void reflect(){
    std::string file_name = "d:/src/my/Chronos/reflect";
    std::string generate_dir = "d:/src/my/Chronos/reflect/generated";
    CodeGenerator cg;
    std::vector<std::string> files ={"head_for_reflect.h","tmp_test.h"};
    cg.generateCodeFromSrc(file_name,files, generate_dir);

}

std::string readFileToString(const std::string file_path){
    std::ifstream is(file_path);
    std::ostringstream os;
    char tmp;
    while(os && is.get(tmp)){
        os.put(tmp);
    }
    return os.str();
}

int main(int argn,const char * args[]){
    std::string str = readFileToString("d:/src/my/Chronos/reflect/test.json");
    json m;
    m = json::parse(str);
    std::cout<<m["src_dir"]<<std::endl;
    reflect();
    return 0;
}