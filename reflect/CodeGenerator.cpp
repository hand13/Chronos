#include "CodeGenerator.h"
#include <fmt/core.h>
#include <iostream>
#include "KlassInfo.h"
#include <fmt/os.h>
#include <string>
#include <vector>
#include "MetaInfoSolver.h"

static std::string underlineClassName(std::string classname){
    while(classname.find("::") != std::string::npos){
        classname = classname.replace(classname.find("::"),2,"_",1);
    }
    return classname;
}

void CodeGenerator::generateCodeFromSrc(const std::string &src_dir
    ,const std::vector<std::string>& srcs,const std::string& target_dir,const std::string& load_fn_name){
    std::vector<std::string> fns;
    for(auto src:srcs){
        ParseContext pc;
        parser.parseFileIntoParseContext(src_dir + "/" + src, pc);
        for(auto klass : pc.klasses){
            fns.push_back(
                generateCodeFromKlass(src,target_dir+"/load_"+underlineClassName(klass.name)+"_generated.cpp",klass));
        }
    }

    generateAllLoadFun(fns,target_dir+"/" + load_fn_name + ".h",load_fn_name);
}


void CodeGenerator::generateAllLoadFun(const std::vector<std::string> fns,const std::string & file_name,const std::string& load_fn_name){
    auto out = fmt::output_file(file_name);
    out.print("#include \"reflect_api/Metaspace.h\"\n");
    for(auto fn : fns){
        out.print("extern LoadFn {};\n",fn);
    }
    out.print("inline void {}(Metaspace* ms){{\n",load_fn_name);
    for(auto fn : fns){
        out.print("    {}(ms);\n",fn);
    }
    out.print("}}");
    out.close();
}

static std::string accessInfoToAccessString(AccessInfo ai){
    switch (ai) {
        case PRIVATE:
        return "Private";
        case PUBLIC:
        return "Public";
        case PROTECTED:
        return "Protected";
        default:
        return "";
    }
}

std::string CodeGenerator::generateCodeFromKlass(const std::string& src_path,const std::string& target_path,const KlassInfo& klass){
    MetaInfoSolver solver;
    solver.solve(klass);
    //todo
    std::cout<<"generated "<<klass.name<<std::endl;
    std::string fn_name = fmt::format("load_{}",underlineClassName(klass.name));
    std::cout<<toString(klass)<<std::endl;
    auto out = fmt::output_file(target_path);

    out.print("#include \"reflect_api/Klass.h\"\n");
    out.print("#include \"reflect_api/Metaspace.h\"\n");
    out.print("#include \"{}\"\n",src_path);

    out.print("void load_{}(Metaspace* ms){{\n",underlineClassName(klass.name));

    out.print("    Klass * klass = new Klass(\"{}\",false,sizeof({}));\n",klass.name,klass.name);

    for(auto f : klass.fileds){
        if(solver.isField(f)){
            if(f.access == PRIVATE){
                continue;
            }
            MetaInfo& mi = solver.fieldMetaInfos[f.name];
            std::string tmp_name = fmt::format("field_{}",f.name);

            out.print("    Field {};\n",tmp_name);
            out.print("    {}.name = \"{}\";\n",tmp_name,f.name);
            out.print("    {}.access = {};\n", tmp_name,accessInfoToAccessString(f.access));
            out.print("    {}.metaInfo.marked = {};\n", tmp_name,mi.marked ? "true":"false");
            out.print("    {}.valueType.rawName = \"{}\";\n",tmp_name,f.type);
            out.print("    {}.valueType.trueName = \"{}\";\n",tmp_name,"");//todo
            out.print("    {}.valueType.type = {};\n",tmp_name,"Value");//todo
            out.print("    {}.valueType.klass = {};\n",tmp_name,"nullptr");
            out.print("    {}.offset = offsetof({},{});\n",tmp_name,klass.name,f.name);

            out.print("    klass->fields.push_back({});\n",tmp_name);
        }
    }
    out.print("    ms->reg({});\n","klass");
    // for(auto m : klass.methods){
    //     out.print("    Method method;\n");
    //     out.print("    method.name = \"{}\";\n",m.name);
    //     out.print("    method.access = \"{}\";\n", toString(m.access));
    //     out.print("    method.returnType = \"{}\";\n",m.returnType);
    //     out.print("    method.offset = offset({},{});\n",klass.name,m.name);
    //     out.print("    klass.methods.push_back(method);\n");
    // }
    out.print("}};");
    out.close();
    return fn_name;
}