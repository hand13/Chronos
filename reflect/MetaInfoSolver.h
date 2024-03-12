#pragma once
#include <map>
#include <set>
#include <string>
#include "MetaInfo.h"
#include "KlassInfo.h"

enum MemberType {
    CLASS,
    CONSTRUCTOR,
    FIELD,
    METHOD
};

struct MetaInfoHelper{
    bool isMacro;
    MemberType memberType;
    std::string markedName;
    MetaInfo metaInfo;
};

class MetaInfoSolver {
    private:
    std::set<std::string> macros;
    std::set<std::string> constructorGenMarked;
    std::set<std::string> fieldsGenMarked;
    std::set<std::string> methodGenMarked;
    public:
    MetaInfo classMetaInfo;
    std::map<std::string, MetaInfo> constructorMetaInfos;
    std::map<std::string, MetaInfo> fieldMetaInfos;
    std::map<std::string, MetaInfo> methodMetaInfos;
    void solve(const KlassInfo& ki);
    static MetaInfoHelper solveFieldName(const std::string& fieldname);
    bool isField(const FieldInfo& fi);
};