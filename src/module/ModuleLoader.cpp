#include "ModuleLoader.h"
#include "ICModule.h"
#include <exception>
#ifdef WIN32
#include <Windows.h>
#endif
namespace Chronos{
    ICModule * ModuleLoader::installModule(const char * path){
        ICModule * result = nullptr;
        ModuleInfo mi;
        #ifdef WIN32
        HMODULE hm = LoadLibraryA(path);
        if(hm){
            mi.dllHandler = hm;
            mi.imp = reinterpret_cast<InstallModuleProc>(GetProcAddress(hm,"InstallModule"));
            mi.ump = reinterpret_cast<UnInstallModuleProc>(GetProcAddress(hm,"UnInstallModule"));
            if(mi.imp == nullptr || mi.ump == nullptr){
                throw std::exception("should not happended");
            }
            result = mi.imp();
            mp[result] = mi;
        }
        #endif
        #ifndef WIN32
            throw std::exception("no imp");
        #endif
        return result;
    }
    void ModuleLoader::uninstallModule(ICModule * module){
        #ifdef WIN32
        ModuleInfo mi = mp[module];
        mi.ump(module);
        FreeLibrary((HMODULE)mi.dllHandler);
        #endif
        #ifndef WIN32
            throw std::exception("no imp");
        #endif
    }
}
