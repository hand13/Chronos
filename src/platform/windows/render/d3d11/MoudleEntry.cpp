
#include <Windows.h>
#include "D3D11RendererModule.h"
#include "module/ICModule.h"
#include <ChronosEngine.h>
#include <module/GlobalValueFix.h>

namespace Chronos {
    extern "C" ChronosEngine * Engine = nullptr;
}

extern "C" __declspec(dllexport) Chronos::ICModule * InstallModule(){
    return new Chronos::D3D11RendererModule();
}
extern "C" __declspec(dllexport) void UninstallModule(Chronos::ICModule * module){
    delete module;
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved ){
    // Perform actions based on the reason for calling.
    switch( fdwReason ) { 
        case DLL_PROCESS_ATTACH:{
            fixGlobalValue(&Chronos::Engine,"Engine");
            // HMODULE main = GetModuleHandle(NULL);
            // int* s = (int*)GetProcAddress(main, "m");
            // m = *s;
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
        }
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
            break;

        case DLL_PROCESS_DETACH:
        
            if (lpvReserved != nullptr) {
                break; // do not do cleanup if process termination scenario
            }
            
         // Perform any necessary cleanup.
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}