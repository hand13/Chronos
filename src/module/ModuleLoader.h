#pragma once
#include <map>

#include "ICModule.h"

namespace Chronos {

typedef ICModule *(*InstallModuleProc)();
typedef void (*UnInstallModuleProc)(ICModule *module);
typedef void *DllHandler;

struct ModuleInfo {
    InstallModuleProc imp;
    UnInstallModuleProc ump;
    DllHandler dllHandler;
};
/**
 * @brief 注意释放
 *
 */

class ModuleLoader {
   private:
    std::map<ICModule *, ModuleInfo> mp;

   public:
    ICModule *installModule(const char *path);
    void uninstallModule(ICModule *module);
    ~ModuleLoader();
};
}  // namespace Chronos