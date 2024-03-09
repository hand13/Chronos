#pragma once
#include "ICModule.h"
#include <map>
namespace Chronos {

    typedef ICModule * (*InstallModuleProc)();
    typedef void (*UnInstallModuleProc)(ICModule * module);
    typedef void *DllHandler;

    struct ModuleInfo {
        InstallModuleProc imp;
        UnInstallModuleProc ump;
        DllHandler dllHandler;
    };

    class ModuleLoader {
        private:
        std::map<ICModule*,ModuleInfo> mp;
        public:
        ICModule * installModule(const char * path);
        void uninstallModule(ICModule * module);
    };
}