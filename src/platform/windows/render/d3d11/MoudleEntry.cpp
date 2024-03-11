
#include <Windows.h>
#include "D3D11RendererModule.h"
#include "module/ICModule.h"
#include "module/IRendererModule.h"
#include "D3D11Renderer.h"
#include <engine/ChronosEngine.h>
#include <module/GlobalValueFix.h>

namespace Chronos {
    extern "C" ChronosEngine * Engine = nullptr;
}


extern "C" __declspec(dllexport) Chronos::ICModule * InstallModule(){
    Chronos::IRendererModule * rm = new Chronos::D3D11RendererModule();
    return rm;
}
extern "C" __declspec(dllexport) void UninstallModule(Chronos::ICModule * module){
    Chronos::D3D11Renderer * dr = dynamic_cast<Chronos::D3D11Renderer*>
        (dynamic_cast<Chronos::IRendererModule*>(module)->getRenderer());
    ComPtr<ID3D11Device> dev = dr->shareDevice();
    ComPtr<ID3D11DeviceContext> dc = dr->shareDeviceCOntext();
    delete module;
    dc->Flush();
    dc = nullptr;
    Chronos::D3D11Renderer::printLiveObject(dev);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved ){
    // Perform actions based on the reason for calling.
    switch( fdwReason ) { 
        case DLL_PROCESS_ATTACH:{
             CoInitializeEx(nullptr, COINIT_MULTITHREADED);//todo
            fixGlobalValue(&Chronos::Engine,"Engine");
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