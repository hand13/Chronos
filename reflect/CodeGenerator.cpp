#include "CodeGenerator.h"

#include <fmt/core.h>
#include <fmt/os.h>

#include <iostream>
#include <string>
#include <vector>

#include "BaseType.h"
#include "KlassInfo.h"
#include "MetaInfoSolver.h"


static std::string underlineClassName(std::string classname) {
    while (classname.find("::") != std::string::npos) {
        classname = classname.replace(classname.find("::"), 2, "_", 1);
    }
    return classname;
}

GenMap CodeGenerator::generateCodeFromSrc(
    const std::string& src_dir, const std::vector<std::string>& srcs,
    const std::string& target_dir,
    const std::vector<std::string>& include_dirs) {
    GenMap result;
    std::vector<std::string> fns;

    for (auto src : srcs) {
        ParseContext pc;
        parser.parseFileIntoParseContext(src_dir + "/" + src, pc, include_dirs);
        for (auto klass : pc.klasses) {
            const std::string file_name = target_dir + "/load_" +
                                          underlineClassName(klass->name) +
                                          "_generated.cpp";
            std::string load_fn_name =
                generateCodeFromKlass(src, file_name, *klass);
            fns.push_back(load_fn_name);
            GenDetail gd(file_name, load_fn_name);
            result[src].push_back(gd);
        }
    }
    return result;
}

void CodeGenerator::generateAllLoadFun(const std::vector<std::string> fns,
                                       const std::string& file_name,
                                       const std::string& load_fn_name) {
    auto out = fmt::output_file(file_name);
    out.print("#include \"reflect_api/Metaspace.h\"\n");
    for (auto fn : fns) {
        out.print("extern LoadFn {};\n", fn);
    }
    out.print("inline void {}(Metaspace* ms){{\n", load_fn_name);
    for (auto fn : fns) {
        out.print("    {}(ms);\n", fn);
    }
    out.print("}}");
    out.close();
}

static std::string accessInfoToAccessString(AccessInfo ai) {
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

static bool isPointer(const std::string& typeName) {
    return typeName.size() > 1 && typeName.at(typeName.length() - 1) == '*';
}

static bool isRef(const std::string& typeName) {
    return typeName.size() > 1 && typeName.at(typeName.length() - 1) == '&';
}

static bool isRightRef(const std::string& typeName) {
    if (isRef(typeName) && typeName.length() > 2) {
        return typeName.at(typeName.length() - 2) == '&';
    }
    return false;
}

static bool isLeftRef(const std::string& typeName) {
    if (isRef(typeName) && !isRightRef(typeName)) {
        return true;
    }
    return false;
}

static std::string removeRef(std::string typeName) {
    if (isRef(typeName)) {
        return typeName.substr(0, typeName.find("&"));
    }
    return typeName;
}

std::string CodeGenerator::generateCodeFromKlass(const std::string& src_path,
                                                 const std::string& target_path,
                                                 const KlassInfo& klass) {
    MetaInfoSolver solver;
    solver.solve(klass);
    // todo
    std::cout << "generated " << klass.name << std::endl;
    std::string fn_name =
        fmt::format("load_{}", underlineClassName(klass.name));
    std::cout << toString(klass) << std::endl;
    auto out = fmt::output_file(target_path);

    out.print("#include <reflect_api/Klass.h>\n");
    out.print("#include <reflect_api/Metaspace.h>\n");
    out.print("#include \"{}\"\n", src_path);

    std::vector<std::string> constructorFuns;
    std::vector<std::string> methodFuncs;

    for (u32 i = 0; i < klass.contrustors.size(); i++) {
        const ConstructorInfo& cinfo = *klass.contrustors[i];
        if (cinfo.access == PRIVATE || cinfo.access == PROTECTED) {
            constructorFuns.push_back("");  // placeholder
            continue;
        }
        std::string constructorFunName =
            fmt::format("{}_constructor_{}", underlineClassName(klass.name), i);
        constructorFuns.push_back(constructorFunName);
        out.print("static void * {}(CallParams& cps){{\n", constructorFunName);
        out.print("    return new {}(", klass.name);
        for (u32 j = 0; j < cinfo.params.size(); j++) {
            if (isLeftRef(cinfo.params[j]->type)) {
                out.print("*({}*)cps[{}].param",
                          removeRef(cinfo.params[j]->type), j);
            } else if (isRightRef(cinfo.params[j]->type)) {
                out.print("std::move(*({}*)cps[{}].param)",
                          removeRef(cinfo.params[j]->type), j);
            } else {
                out.print("*({}*)cps[{}].param", cinfo.params[j]->type, j);
            }
            if (j != cinfo.params.size() - 1) {
                out.print(",");
            }
        }
        out.print(");\n");
        out.print("}}\n");
    }

    out.print("void load_{}(Metaspace* ms){{\n",
              underlineClassName(klass.name));

    out.print("    Klass * klass = new Klass(\"{}\",false,sizeof({}));\n",
              klass.name, klass.name);

    for (auto& pf : klass.fileds) {
        const FieldInfo& f = *pf;
        if (solver.isField(f)) {
            if (f.access == PRIVATE || f.access == PROTECTED) {
                continue;
            }
            MetaInfo& mi = solver.fieldMetaInfos[f.name];
            std::string tmp_name = fmt::format("field_{}", f.name);

            out.print("    Field {};\n", tmp_name);
            out.print("    {}.name = \"{}\";\n", tmp_name, f.name);
            out.print("    {}.access = {};\n", tmp_name,
                      accessInfoToAccessString(f.access));
            out.print("    {}.metaInfo.marked = {};\n", tmp_name,
                      mi.marked ? "true" : "false");
            out.print("    {}.valueType.rawName = \"{}\";\n", tmp_name, f.type);
            out.print("    {}.valueType.trueName = \"{}\";\n", tmp_name,
                      "");  // todo
            out.print("    {}.valueType.type = {};\n", tmp_name,
                      "Value");  // todo
            out.print("    {}.valueType.klass = {};\n", tmp_name, "nullptr");
            out.print("    {}.offset = offsetof({},{});\n", tmp_name,
                      klass.name, f.name);

            out.print("    klass->fields.push_back({});\n", tmp_name);
        }
    }
    for (u32 i = 0; i < klass.contrustors.size(); i++) {
        const ConstructorInfo& cinfo = *klass.contrustors[i];
        if (cinfo.access == PRIVATE || cinfo.access == PROTECTED) {
            continue;
        }
        std::string constructorFunName = constructorFuns[i];
        std::string tmpname = fmt::format("constructor_{}", i);
        out.print("    Constructor {};\n", tmpname);
        out.print("    {}.access = {};\n", tmpname,
                  accessInfoToAccessString(cinfo.access));
        out.print("    {}.metaInfo.marked = {};\n", tmpname, "true");  // todo

        for (auto& pmpi : cinfo.params) {
            const MethodParamInfo& mpi = *pmpi;
            std::string tmpparamname = fmt::format("param_{}_{}", mpi.name, i);
            out.print("    MethodParam {};\n", tmpparamname);
            out.print("    {}.name = \"{}\";\n", tmpparamname, mpi.name);

            if (isRightRef(mpi.type)) {
                out.print("    {}.type.type = {};\n", tmpparamname,
                          "RightRef");  // todo
            } else if (isLeftRef(mpi.type)) {
                out.print("    {}.type.type = {};\n", tmpparamname,
                          "Ref");  // todo
            } else if (isPointer(mpi.type)) {
                out.print("    {}.type.type = {};\n", tmpparamname,
                          "Pointer");  // todo
            } else {
                out.print("    {}.type.type = {};\n", tmpparamname,
                          "Value");  // todo
            }
            out.print("    {}.type.rawName = \"{}\";\n", tmpparamname,
                      mpi.type);  // todo
            out.print("    {}.type.trueName= \"{}\";\n", tmpparamname,
                      "");  // todo
            out.print("    {}.type.klass= {};\n", tmpparamname,
                      "nullptr");  // todo
            out.print("    {}.params.push_back({});\n", tmpname, tmpparamname);
        }
        out.print("    {}.setFunCall({});\n", tmpname, constructorFunName);
        out.print("    klass->constructors.push_back({});\n", tmpname);
    }

    out.print("    ms->reg({});\n", "klass");
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