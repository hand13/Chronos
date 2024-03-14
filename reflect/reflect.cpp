#include "CodeGenerator.h"
#include <string>
#include <vector>
void reflect(){
    std::string file_name = "d:/src/my/Chronos/reflect";
    std::string generate_dir = "d:/src/my/Chronos/reflect/generated";
    CodeGenerator cg;
    std::vector<std::string> files ={"head_for_reflect.h","tmp_test.h"};
    cg.generateCodeFromSrc(file_name,files, generate_dir);
}

int main(){
    reflect();
    return 0;
}