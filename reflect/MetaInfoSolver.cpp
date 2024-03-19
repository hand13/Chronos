#include "MetaInfoSolver.h"
#include <cstring>


MetaInfoHelper MetaInfoSolver::solveFieldName(const std::string& fieldname){

    static const char * gcstr = "generated_class";
    static const char * gfstr= "generated_field_";
    static const char * gmstr = "generated_method_";

    MetaInfoHelper mh;
    mh.isMacro = false;

    if(fieldname == gcstr){
        mh.isMacro = true;
        mh.memberType = CLASS;
        mh.metaInfo.marked = true;

    }else if(fieldname.length() > strlen(gfstr)&& fieldname.find(gfstr) == 0) {
        mh.isMacro = true;
        mh.memberType = FIELD;
        mh.markedName = fieldname.substr(strlen(gfstr));
        mh.metaInfo.marked = true;
    }else if(fieldname.length() > strlen(gmstr) && fieldname.find(gmstr) ==0){
        mh.isMacro = true;
        mh.memberType = METHOD;
        mh.markedName = fieldname.substr(strlen(gmstr));
        mh.metaInfo.marked = true;
    }
    return mh;
}

void MetaInfoSolver::solve(const KlassInfo& ki){

    for(auto f : ki.fileds){
        MetaInfoHelper mh = solveFieldName(f->name);
        if(mh.isMacro){
            macros.insert(f->name);
            switch (mh.memberType) {
                case CLASS:
                classMetaInfo = mh.metaInfo;
                break;
                case CONSTRUCTOR:
                constructorGenMarked.insert(mh.markedName);
                constructorMetaInfos[mh.markedName] = mh.metaInfo;
                break;
                case FIELD:
                fieldsGenMarked.insert(mh.markedName);
                fieldMetaInfos[mh.markedName] = mh.metaInfo;
                break;
                case METHOD:
                methodGenMarked.insert(mh.markedName);
                methodMetaInfos[mh.markedName] = mh.metaInfo;
                break;
            }
        }
    }

    MetaInfo mi;mi.marked = false;
    for(auto c : ki.contrustors){
        if(constructorGenMarked.find(c->name) ==constructorGenMarked.end()){
            constructorMetaInfos[c->name] = mi;
        }
    }
    for(auto f : ki.fileds){
        if(macros.find(f->name) != macros.end()){
            continue;
        }
        if(fieldsGenMarked.find(f->name) ==fieldsGenMarked.end()){
            fieldMetaInfos[f->name] = mi;
        }
    }
    for(auto m : ki.methods){
        if(methodGenMarked.find(m->name) == methodGenMarked.end()){
            methodMetaInfos[m->name] = mi;
        }
    }
}
bool MetaInfoSolver::isField(const FieldInfo& fi){

    return fieldMetaInfos.find(fi.name) != fieldMetaInfos.end();

}