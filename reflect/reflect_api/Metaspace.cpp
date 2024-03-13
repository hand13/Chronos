#include "Metaspace.h"
#include "BaseType.h"

Metaspace::Metaspace(){
    loadPrimitiveKlass();
    loadPreDefinedKlass();
}

void Metaspace::loadPrimitiveKlass(){
    reg(new Klass("bool",true,sizeof(bool)));
    reg(new Klass("i8",true,sizeof(i8)));
    reg(new Klass("i16",true,sizeof(i16)));
    reg(new Klass("i32",true,sizeof(i32)));
    reg(new Klass("i64",true,sizeof(i64)));
    reg(new Klass("u8",true,sizeof(u8)));
    reg(new Klass("u16",true,sizeof(u16)));
    reg(new Klass("u32",true,sizeof(u32)));
    reg(new Klass("u64",true,sizeof(u64)));
    reg(new Klass("f32",true,sizeof(f32)));
    reg(new Klass("f64",true,sizeof(f64)));

    reg(new Klass("char",true,sizeof(char)));
    reg(new Klass("short",true,sizeof(short)));
    reg(new Klass("int",true,sizeof(int)));
    reg(new Klass("long",true,sizeof(long)));
    reg(new Klass("long long",true,sizeof(long long)));

    reg(new Klass("unsigned char",true,sizeof(unsigned char)));
    reg(new Klass("unsigned short",true,sizeof(unsigned short)));
    reg(new Klass("unsigned int",true,sizeof(unsigned int)));
    reg(new Klass("unsigned long",true,sizeof(unsigned long)));
    reg(new Klass("unsigned long long",true,sizeof(unsigned long long)));

    reg(new Klass("float",true,sizeof(float)));
    reg(new Klass("double",true,sizeof(float)));
}
void Metaspace::loadPreDefinedKlass(){

}

void Metaspace::load(const std::string& file_path){
    //todo
}

void Metaspace::load(LoadFn fn){
    fn(this);
}

void Metaspace::reg(Klass* klass){
    klasses[klass->name] = klass;
}

Klass *Metaspace::getKlass(const std::string& name){
    if(klasses.find(name) != klasses.end()){
        return klasses.at(name);
    }
    return nullptr;
}

void Metaspace::solveLink(){
    for(auto k : klasses){
        for(auto f : k.second->fields){
            if(klasses.find(f.valueType.rawName) != klasses.end()){
                f.valueType.klass = klasses.at(f.valueType.rawName);
            }
        }
    }
}

Metaspace::~Metaspace(){
    for(auto k : klasses){
        if(k.second){
            delete k.second;
        }
    }
}