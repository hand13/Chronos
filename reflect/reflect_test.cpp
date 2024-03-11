#include "CodeGenerator.h"
int main(){
    std::string file_name = "head_for_reflect.h";
    std::string generate_dir = "generated";
    CodeGenerator cg;
    cg.generateCodeFromSrc(file_name, generate_dir);
    return 0;
}