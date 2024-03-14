#pragma once
#include "Klass.h"
#include <map>
#include <string>

class Metaspace;
typedef void (LoadFn)(Metaspace* ms);
class Metaspace{
    private:
    std::map<std::string,Klass*> klasses;
    void loadPrimitiveKlass();
    void loadPreDefinedKlass();
    public:
    Metaspace();
    void load(const std::string& file_path);
    void load(LoadFn fn);
    void reg(Klass* klass);
    Klass *getKlass(const std::string& name);
    void solveLink();
    ~Metaspace();
};