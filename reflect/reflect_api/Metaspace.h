#pragma once
#include "Klass.h"
#include <map>
#include <string>
#include <vcruntime_typeinfo.h>

class Metaspace;
typedef void (LoadFn)(Metaspace* ms);
class Metaspace{
    private:
    static const char * typenameclass;
    static const char * typenamestruct;
    std::map<std::string,Klass*> klasses;
    void loadPrimitiveKlass();
    void loadPreDefinedKlass();
    public:
    Metaspace();
    /**
     * @brief todo 直接加载binary
     * 
     * @param file_path 
     */
    void load(const std::string& file_path);
    /**
     * @brief 执行fn注册class
     * 
     * @param fn 
     */
    void load(LoadFn fn);
    /**
     * @brief 注册class
     * 
     * @param klass 
     */
    void reg(Klass* klass);
    /**
     * @brief Get the Klass object from class name
     * 
     * @param name 
     * @return Klass* 
     */
    Klass *getKlass(const std::string& name);
    /**
     * @brief Get the Klass With Type Info Name object
     * 
     * @param typeinfoname 
     * @return Klass* 
     */
    Klass * getKlassWithTypeInfoName(const std::string& typeinfoname);
    /**
     * @brief Get the Klass object from type
     * 
     * @tparam T 
     * @return Klass* 
     */
    template<typename T>
    Klass * getKlass(){
        const std::string typeinfoname = typeid(T).name();
        return getKlassWithTypeInfoName(typeinfoname);
    }

    /**
     * @brief 解析符号引用
     * 
     */
    void solveLink();

    inline Klass* charclass(){return getKlass("char");}
    inline Klass* shortclass(){return getKlass("short");}
    inline Klass* intclass(){return getKlass("int");}
    inline Klass* longclass(){return getKlass("long");}
    inline Klass* longlongclass(){return getKlass("long long");}

    inline Klass* ucharclass(){return getKlass("unsigned char");}
    inline Klass* ushortclass(){return getKlass("unsigned short");}
    inline Klass* uintclass(){return getKlass("unsigned int");}
    inline Klass* ulongclass(){return getKlass("unsigned long");}
    inline Klass* ulonglongclass(){return getKlass("unsigned long long");}

    inline Klass* floatclass(){return getKlass("float");}
    inline Klass* doubleclass(){return getKlass("double");}

    inline Klass* i8class(){return getKlass("i8");}
    inline Klass* i16class(){return getKlass("i16");}
    inline Klass* i32class(){return getKlass("i32");}
    inline Klass* i64class(){return getKlass("i64");}

    inline Klass* u8class(){return getKlass("u8");}
    inline Klass* u16class(){return getKlass("u16");}
    inline Klass* u32class(){return getKlass("u32");}
    inline Klass* u64class(){return getKlass("u64");}

    inline Klass* f32class(){return getKlass("f32");}
    inline Klass* f64class(){return getKlass("f64");}

    ~Metaspace();
};