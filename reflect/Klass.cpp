
#include "Klass.h"
#include <string>
std::string toString(const Access& a){
    std::string res;
    switch (a) {
        case PROTECTED:
        res = "protected";
        break;
        case PUBLIC:
        res = "public";
        break;
        case PRIVATE:
        res = "private";
        break;
    }
    return res;
}
std::string toString(const MethodParam& a){
    return a.type + " " + a.name;
}
std::string toString(const Method& a){
    std::string ms = toString(a.access) + " " + a.returnType + " " + a.name + "(";
    for(auto m : a.params){
        ms.append(toString(m));
        ms.append(",");
    }
    ms.append(");");
    return ms;
}
std::string toString(const Field& a){
    return toString(a.access) + " " + a.type + " "+a.name + ";";
}
std::string toString(const Constructor& a){
    std::string ms = toString(a.access)+" " + a.name + "(";
    for(auto m : a.params){
        ms.append(toString(m));
        ms.append(",");
    }
    ms.append(");");
    return ms;
}
std::string toString(const Klass& a){
    std::string res;
    res = std::string("class ") + a.name + "{\n";
    for(auto c : a.contrustors){
        res.append(toString(c));
        res.append("\n");
    }
    for(auto f : a.fileds){
        res.append(toString(f));
        res.append("\n");
    }
    for(auto m : a.methods){
        res.append(toString(m));
        res.append("\n");
    }
    res.append("\n}");
    return res;
}