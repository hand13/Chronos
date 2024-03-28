#include "ModuleLoader.h"

#include <exception>

#include "ICModule.h"

#ifdef WIN32
#include <Windows.h>
#endif
namespace Chronos {
ICModule* ModuleLoader::installModule(const char* path) {
    ICModule* result = nullptr;
    ModuleInfo mi;
#ifdef WIN32
    HMODULE hm = LoadLibraryA(path);
    if (hm) {
        mi.dllHandler = hm;
        mi.imp = reinterpret_cast<InstallModuleProc>(
            GetProcAddress(hm, "InstallModule"));
        mi.ump = reinterpret_cast<UnInstallModuleProc>(
            GetProcAddress(hm, "UninstallModule"));
        if (mi.imp == nullptr || mi.ump == nullptr) {
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
void ModuleLoader::uninstallModule(ICModule* module) {
#ifdef WIN32
    ModuleInfo mi = mp[module];
    mi.ump(module);
    FreeLibrary((HMODULE)mi.dllHandler);
#endif
#ifndef WIN32
    throw std::exception("no imp");
#endif
}
ModuleLoader::~ModuleLoader() {
    for (auto iter = mp.begin(); iter != mp.end();) {
        uninstallModule(iter->first);
        iter = mp.erase(iter);
    }
}
}  // namespace Chronos
