#include "WinChronosWindow.h"
#include <cstddef>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <dxgicommon.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <minwinbase.h>
#include <minwindef.h>
#include <winbase.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>
#include "Utils.h"
#include "../../Log.h"
namespace  Chronos {
    static  LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    WinChronosWindow::WinChronosWindow() {
        hWnd = NULL;
        width = 800;
        height = 600;
    }
    void WinChronosWindow::init(){
        wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, TEXT("Chronos"), NULL };
        wc.hCursor = LoadCursor(NULL,IDC_ARROW);
        ::RegisterClassEx(&wc);
        hWnd = ::CreateWindow(wc.lpszClassName, TEXT("Chronos"),
         WS_OVERLAPPEDWINDOW, 100, 100,width,height, NULL, NULL
         , wc.hInstance, this);
        // Show the window
        this->createD3D11DeviceAndSwapChain();
        this->createRenderTargetView();
    }

    void WinChronosWindow::show() {
        ::ShowWindow(hWnd, SW_SHOWDEFAULT);
        ::UpdateWindow(hWnd);
    }

    void WinChronosWindow::getSize(unsigned int & w,unsigned int & h)  {
        w = width;
        h = height;
    }

    void WinChronosWindow::resize(WPARAM wParam,unsigned int w,unsigned int h) {
        width = w;
        height = h;
        rtv->Release();
        HRESULT hr =  swapChain->ResizeBuffers(2, 0,0, DXGI_FORMAT_R8G8B8A8_UNORM,0);
        ThrowIfFailed(hr);
        createRenderTargetView();

        D3D11_VIEWPORT viewport;
        viewport.TopLeftX = 0.f;
        viewport.TopLeftY = 0.f;
        viewport.Width = w;
        viewport.Height = h;
        viewport.MinDepth = D3D11_MIN_DEPTH;
        viewport.MaxDepth = D3D11_MAX_DEPTH;
        deviceContext->RSSetViewports(1, &viewport);
        // RECT rect = {0,0,static_cast<LONG>(w),static_cast<LONG>(h)};
        // SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
    }

    void WinChronosWindow::draw() {
        deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), NULL);
        float color[] = {0.8f,0.1f,0.3f,1.f};
        deviceContext->ClearRenderTargetView(rtv.Get(), color);
        ThrowIfFailed(swapChain->Present(1, 0));
    }

    void WinChronosWindow::loop() {
        bool done = false;
        MSG msg;
        while(1){
            while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                if (msg.message == WM_QUIT){
                    done = true;
                    break;
                }
            }
            if (done) {
                break;
            }
            draw();
        }
    }

    void WinChronosWindow::createRenderTargetView() {
        ID3D11Texture2D * pBackBuffer;
        HRESULT hr = swapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID *)&pBackBuffer);
        ThrowIfFailed(hr);
        hr = d3d11Device->CreateRenderTargetView(pBackBuffer,NULL,rtv.GetAddressOf());
        ThrowIfFailed(hr);
        pBackBuffer->Release();
    }

    void WinChronosWindow::createD3D11DeviceAndSwapChain() {
        D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd,sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = true;

        HRESULT hr;
        UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        #if defined (_DEBUG)
        flags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif
        hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,flags, &featureLevel, 1, D3D11_SDK_VERSION
        , &sd, swapChain.GetAddressOf(),d3d11Device.GetAddressOf(), NULL,deviceContext.GetAddressOf());
        ThrowIfFailed(hr);

    }

    WinChronosWindow::~WinChronosWindow() {
        Log(TEXT("啊我死了"));
    }

    static WinChronosWindow* GetWindowFromLParam(LPARAM lParam) {
        void * data = ((LPCREATESTRUCT)lParam)->lpCreateParams;
        WinChronosWindow* ptr = reinterpret_cast<WinChronosWindow*>(data);
        return ptr;
    }

    LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        static WinChronosWindow * wcw = nullptr;
        switch (msg)
        {
        case WM_CREATE:
            wcw = GetWindowFromLParam(lParam);
            break;
        case WM_SIZE:{
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            wcw->resize(wParam,width,height);
            return 0;
        }
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        }
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

}