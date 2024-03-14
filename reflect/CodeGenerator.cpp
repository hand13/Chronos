#include "CodeGenerator.h"
#include <fmt/core.h>
#include <iostream>
#include "KlassInfo.h"
#include <fmt/os.h>
#include <string>
#include <vector>
#include "MetaInfoSolver.h"
#include <filesystem>

static std::string underlineClassName(std::string classname){
    while(classname.find("::") != std::string::npos){
        classname = classname.replace(classname.find("::"),2,"_",1);
    }
    return classname;
}

void CodeGenerator::generateCodeFromSrc(const std::string &src_dir
    ,const std::vector<std::string>& srcs,const std::string& target_dir){
    std::vector<std::string> fns;
    for(auto src:srcs){
        ParseContext pc;
        parser.parseFileIntoParseContext(src_dir + "/" + src, pc);
        for(auto klass : pc.klasses){
            fns.push_back(
                generateCodeFromKlass(src,target_dir+"/load_"+underlineClassName(klass.name)+"_generated.cpp",klass));
        }
    }

    generateAllLoadFun(fns,target_dir+"/" + "load_all.h");
}


void CodeGenerator::generateAllLoadFun(const std::vector<std::string> fns,const std::string & file_name){
    auto out = fmt::output_file(file_name);
    out.print("#include \"reflect_api/Metaspace.h\"\n");
    for(auto fn : fns){
        out.print("extern LoadFn {};\n",fn);
    }
    out.print("inline void loadAll(Metaspace* ms){{\n");
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

static void listAllHeaderFile(const std::filesystem::path& global_dir_path,const std::filesystem::path&dir_path,std::vector<std::string>& result){

    // std::filesystem::directory_iterator id(dir_path);
    // for(auto f:id ){
    //     if(!f.is_directory()){

    //         std::string pstr= f.path().filename().u8string();
    //         if(pstr.length() > 2&& pstr.compare(pstr.size() - 2,2,".h") == 0){
    //             std::filesystem::path relPath = f.path().lexically_relative(global_dir_path);
    //             result.push_back(relPath.u8string());
    //         }

    //     }else {
    //         listAllHeaderFile(global_dir_path, f.path(), result);
    //     }
    // }
}

void CodeGenerator::generateCodeFromSrc(const std::string &src_dir
    ,const std::vector<std::string>* srcs,const std::string& target_dir){
    if(srcs != nullptr){
        return generateCodeFromSrc(src_dir,*srcs,target_dir);
    }
    std::vector<std::string> ss;
    listAllHeaderFile("",src_dir,ss);
    if(ss.size() > 0){
        return generateCodeFromSrc(src_dir,ss,target_dir);
    }
}
