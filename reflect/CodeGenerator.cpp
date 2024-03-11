#include "CodeGenerator.h"
#include <iostream>
#include "KlassInfo.h"
#include <fmt/os.h>

void CodeGenerator::generateCodeFromSrc(const std::string &src_path,const std::string& target_dir){
    ParseContext pc;
    parser.parseFileIntoParseContext(src_path, pc);
    for(auto klass : pc.klasses){
        generateCodeFromKlass(target_dir+"/"+klass.name+"_generated.h",klass);
    }
}
void CodeGenerator::generateCodeFromKlass(const std::string& target_path,const KlassInfo& klass){
    //todo
    std::cout<<"generated "<<klass.name<<std::endl;
    std::cout<<toString(klass)<<std::endl;
    auto out = fmt::output_file(target_path);
    out.print("#pragma once\n");
    out.print("#include \"Klass.h\"\n");
    out.print("class static_{}{{\n", klass.name);
    out.print("    private:\n");
    out.print("    Klass klass;\n");
    out.print("    public:\n");
    out.print("    static_{}(){{\n",klass.name);

    for(auto f : klass.fileds){
        out.print("    Field field;\n");
        out.print("    field.name = \"{}\";\n",f.name);
        out.print("    field.access = \"{}\";\n", toString(f.access));
        out.print("    field.type = \"{}\";\n",f.type);
        out.print("    field.offset = offset({},{});\n",klass.name,f.name);
        out.print("    klass.fields.push_back(field);\n");
    }
    for(auto m : klass.methods){
        out.print("    Method method;\n");
        out.print("    method.name = \"{}\";\n",m.name);
        out.print("    method.access = \"{}\";\n", toString(m.access));
        out.print("    method.returnType = \"{}\";\n",m.returnType);
        out.print("    method.offset = offset({},{});\n",klass.name,m.name);
        out.print("    klass.methods.push_back(method);\n");
    }

    // out.print("void *construct");
    out.print("    \n");
    out.print("    }}\n");
    out.print("}};");
    out.close();
}