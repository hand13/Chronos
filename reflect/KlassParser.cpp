#include "clang-c/CXFile.h"
#include "clang-c/CXSourceLocation.h"
#include "clang-c/CXString.h"
#include <clang-c/Index.h>
#include <exception>
#include <stack>
#include <vector>
#include "KlassParser.h"
#include "KlassInfo.h"

template<typename T>
static T * getTopPointer(std::vector<T>& s){
    return &s[s.size()-1];
}
static AccessInfo fromCXSpecifierToAccess(CX_CXXAccessSpecifier as){
    switch (as) {
        case CX_CXXPrivate:
        return PRIVATE;
        case CX_CXXPublic:
        return PUBLIC;
        case CX_CXXProtected:
        return PROTECTED;
        default:
            throw std::exception("nonono");
    }
};
// static std::ostream& operator<<(std::ostream& stream,const CXString& str){
//     stream << clang_getCString(str);
//     clang_disposeString(str);
//     return stream;
// }

// static void printCursorInfo(CXCursor& c){
//         std::cout<<"Cursor '"<<clang_getCursorSpelling(c)<<"' of kind '"
//         << clang_getCursorKindSpelling(clang_getCursorKind(c))<<"'\n";
// }
static std::string getTypeName(CXType& t){
    CXString cs = clang_getTypeSpelling(t);
    std::string name = clang_getCString(cs);
    clang_disposeString(cs);
    return name;
}

// static void printTypeInfo(CXType& t){
//     std::cout<<"type '"<< clang_getTypeSpelling(t)<<"' of kind '"<<std::endl;
// }
static std::string getCursorName(const CXCursor& c){
    CXString cs = clang_getCursorSpelling(c);
    std::string name = clang_getCString(cs);
    clang_disposeString(cs);
    return name;
}
static std::string getFileNameFromCursor(const CXCursor& c){
        CXSourceLocation cl =  clang_getCursorLocation(c);
        CXFile file;
        clang_getSpellingLocation(cl,&file,nullptr,nullptr,nullptr);
        if(!file){
            throw std::exception("no file");
        }
        CXString str = clang_getFileName(file);
        std::string filename = clang_getCString(str);
        clang_disposeString(str);
        return filename;
}

KlassParser::KlassParser(){
     index =clang_createIndex(0, 0);
}

KlassParser::~KlassParser(){
    clang_disposeIndex(index);
}

std::string fetchTypename(CXType& type){
    std::string simpleName = getTypeName(type);
    std::string typedefName;
    std::string canonicalName;
    {
        CXCursor tmp = clang_getTypeDeclaration(type);
        CXType rt = clang_getTypedefDeclUnderlyingType(tmp);
        typedefName = getTypeName(rt);
    }
    {
        CXType ts=  clang_getCanonicalType(type);
        canonicalName = getTypeName(ts);
    }
    if(typedefName != ""){
        return simpleName;
    }
    return canonicalName;
}

void KlassParser::parseFileIntoParseContext(const std::string& file_path,ParseContext& pc,const std::vector<std::string>& include_dirs){

    const char *file_name = file_path.c_str();
    const char * command_line_args[] = {"-x","c++","-DREFLECT_GEN"};
    std::vector<const char*> commands(include_dirs.size() + sizeof(command_line_args)/sizeof(char*));
    // commands.reserve(include_dirs.size() + sizeof(command_line_args)/sizeof(char*));

    std::vector<std::string> inc_commands;
    for(auto ind : include_dirs){
        inc_commands.push_back("-I"+ind);
    }
    int offset = 0;
    for(auto c : command_line_args){
        commands[offset] = c;
        offset++;
    }
    for(auto& s : inc_commands){
        commands[offset] = s.c_str();
        offset++;
    }
    // tmp.push_back(nullptr);

    CXTranslationUnit unit = clang_parseTranslationUnit(index, 
    file_name,commands.data(),static_cast<int>(commands.size()), nullptr, 0, CXTranslationUnit_None);
    if(unit == nullptr){
        throw std::exception("should not happended");
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    pc.file_name = file_name;
    clang_visitChildren(cursor,[](CXCursor c,CXCursor parent,CXClientData clientData){
        ParseContext * pc = reinterpret_cast<ParseContext*>(clientData);
        std::string fname = getFileNameFromCursor(c);
        if(fname != pc->file_name){
            return CXChildVisit_Continue;
        }

        // printCursorInfo(c);
        CXChildVisitResult result = CXChildVisit_Continue;//略过
        if(pc->stack.size() != 0 && pc->cursorStack.size() != 0){
            CXCursor&m = pc->cursorStack.top();
            if(m.xdata != parent.xdata || m.kind != parent.kind){
                pc->cursorStack.pop();
                pc->stack.pop();
            }
        }
        switch (c.kind) {
            case CXCursor_StructDecl:{
                    result = CXChildVisit_Recurse;
                    KlassInfo klass;
                    CXType type = clang_getCursorType(c);
                    klass.name = fetchTypename(type);
                    pc->klasses.push_back(klass);
                    pc->stack.push(getTopPointer(pc->klasses));
                    pc->cursorStack.push(c);
                }
                result = CXChildVisit_Recurse;
                break;
            case CXCursor_ClassDecl:{
                    KlassInfo klass;
                    CXType type = clang_getCursorType(c);
                    klass.name = fetchTypename(type);
                    pc->klasses.push_back(klass);
                    pc->stack.push(getTopPointer(pc->klasses));
                    pc->cursorStack.push(c);

                }
                result = CXChildVisit_Recurse;
                break;

            case CXCursor_Constructor:{
                    ConstructorInfo constructor;
                    constructor.name = getCursorName(c);
                    constructor.access = fromCXSpecifierToAccess(clang_getCXXAccessSpecifier(c));
                    KlassInfo* klass = dynamic_cast<KlassInfo*>(pc->stack.top());
                    if(klass == nullptr){
                        throw std::exception("should not happended");
                    }
                    klass->contrustors.push_back(constructor);
                    pc->stack.push(getTopPointer(klass->contrustors));
                    pc->cursorStack.push(c);
                }
                result = CXChildVisit_Recurse;
                break;
            case CXCursor_FieldDecl:{

                    FieldInfo field;
                    field.access = fromCXSpecifierToAccess(clang_getCXXAccessSpecifier(c));
                    field.name = getCursorName(c);
                    CXType type = clang_getCursorType(c);
                    field.type = fetchTypename(type);
                    KlassInfo* klass = dynamic_cast<KlassInfo*>(pc->stack.top());
                    if(klass == nullptr){
                        throw std::exception("should not happended");
                    }
                    klass->fileds.push_back(field);
                    pc->stack.push(getTopPointer(klass->fileds));
                    pc->cursorStack.push(c);
                }
                result = CXChildVisit_Recurse;
                break;
            case CXCursor_CXXMethod:{

                    MethodInfo method;
                    method.name = getCursorName(c);
                    method.access = fromCXSpecifierToAccess(clang_getCXXAccessSpecifier(c));
                    CXType type = clang_getCursorType(c);
                    CXType rt =  clang_getResultType(type);
                    method.returnType = getTypeName(rt);

                    KlassInfo* klass = dynamic_cast<KlassInfo*>(pc->stack.top());
                    if(klass == nullptr){
                        throw std::exception("should not happended");
                    }
                    klass->methods.push_back(method);
                    pc->stack.push(getTopPointer(klass->methods));
                    pc->cursorStack.push(c);
                }
                result = CXChildVisit_Recurse;
                break;
            case CXCursor_ParmDecl:{
                    MethodParamInfo mp;
                    MethodInfo* method = dynamic_cast<MethodInfo*>(pc->stack.top());
                    ConstructorInfo * constructor = dynamic_cast<ConstructorInfo*>(pc->stack.top());
                    if(method == nullptr && constructor == nullptr){
                        throw std::exception("should not happended");
                    }

                    mp.name = getCursorName(c);
                    CXType type = clang_getCursorType(c);
                    mp.type = getTypeName(type);

                    if(method != nullptr){
                        method->params.push_back(mp);
                    }else {
                        constructor->params.push_back(mp);
                    }
                }
                result = CXChildVisit_Continue;//没必要继续向下了
                break;
            case CXCursor_Namespace:{
                result = CXChildVisit_Recurse;
                break;
            }
            default:
                result = CXChildVisit_Continue;
        }
        return result;
    },&pc);
    clang_disposeTranslationUnit(unit);
}