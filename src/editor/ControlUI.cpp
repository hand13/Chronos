// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <d3d11.h>
#include <exception>
#include <minwinbase.h>
#include <rpcndr.h>
#include <tchar.h>
#include <winuser.h>
#include "ControlUI.h"
#include <platform/windows/render/d3d11/D3D11Renderer.h>

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Data
namespace Chronos {

    ControlUI::ControlUI(){
        ZeroMemory(&wc,sizeof(wc));
        finished = false;
        cleaned = false;
        resizeWidth = 0;
        resizeHeight = 0;
    }

    void ControlUI::cleanResource(){
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        rtv = nullptr;
        swapChain = nullptr;

        ::DestroyWindow(hWnd);
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
    }

    void ControlUI::show(){
        ::ShowWindow(hWnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hWnd);
    }

    void ControlUI::init(Renderer * renderer){
        D3D11Renderer * dr = dynamic_cast<D3D11Renderer*>(renderer);
        if(dr == nullptr){
            throw std::exception("should not happended");
        }
        device = dr->shareDevice();
        deviceContext = dr->shareDeviceCOntext();
        wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("ImGui Example"), NULL };
        ::RegisterClassEx(&wc);
        hWnd = ::CreateWindow(wc.lpszClassName, _T("Dear ImGui DirectX11 Example"), WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance,this);
        createSwapChain();
        // Show the window
        // ::ShowWindow(hWnd, SW_SHOWDEFAULT);
        // ::UpdateWindow(hWnd);
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX11_Init(device.Get(), deviceContext.Get());


    }
    void ControlUI::runInLoop(){

        if(finished){
            if(!cleaned){
                cleanResource();
                cleaned = true;
            }
            return;
        }

        MSG msg;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        while (::PeekMessage(&msg, hWnd, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        if(resizeHeight != 0 && resizeWidth != 0){
            rtv->Release();
            swapChain->ResizeBuffers(0, resizeWidth, resizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            resizeWidth = 0;
            resizeHeight = 0;
            createRTV();
        }
        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            showWindow();
            // ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            // ImGui::End();
        }

        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), NULL);
        deviceContext->ClearRenderTargetView(rtv.Get(), clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swapChain->Present(1, 0); // Present with vsync
    }
    void ControlUI::quit(){
        finished = true;
    }
    bool ControlUI::createSwapChain(){

        IDXGIFactory*  factory =nullptr;
        IDXGIDevice * pDXGIDevice = nullptr;
        ThrowIfFailed(device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice));
        IDXGIAdapter * pDXGIAdapter = nullptr;
        ThrowIfFailed(pDXGIDevice->GetAdapter( &pDXGIAdapter));
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&factory);
        //todo 不知道需不需要release


        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        if(FAILED(factory->CreateSwapChain(device.Get(),&sd,swapChain.GetAddressOf()))){
            throw std::exception("should not happended");
        }
        createRTV();

        return true;
    }
    bool ControlUI::createRTV(){

        ID3D11Texture2D* pBackBuffer;
        swapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        device->CreateRenderTargetView(pBackBuffer, NULL, rtv.GetAddressOf());
        pBackBuffer->Release();
        return true;
    }

    ControlUI::~ControlUI(){
        if(!cleaned){
            cleanResource();
        }
    }
    bool ControlUI::isStop(){
        return finished;
    }
}





// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static Chronos::ControlUI* cui = nullptr;
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_CREATE:{
            void * data = ((LPCREATESTRUCT)lParam)->lpCreateParams;
            cui = reinterpret_cast<Chronos::ControlUI*>(data);
        }
        return 0;
    case WM_SIZE:
        if(cui != nullptr){
            cui->setResizeWidth(LOWORD(lParam));
            cui->setResizeHeight(HIWORD(lParam));
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        if(cui != nullptr){
            cui->quit();
        }
        return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}
