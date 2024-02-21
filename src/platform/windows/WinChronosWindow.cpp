#include "WinChronosWindow.h"
#include <cstddef>
#include <d3d10shader.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgi.h>
#include <dxgicommon.h>
#include <dxgiformat.h>
#include <dxgitype.h>
#include <string.h>
#include <minwinbase.h>
#include <minwindef.h>
#include <vector>
#include <winbase.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>
#include "Utils.h"
#include "../../Log.h"
#include "../../Utils.h"
#include "../../render/d3d11/ChronosD3D11Texture2D.h"
#include <d3d11shader.h>
namespace  Chronos {
    static  LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    WinChronosWindow::WinChronosWindow() {
        hWnd = NULL;
        width = 800;
        height = 600;
        sceneTexture = nullptr;
        cursorCapture = false;
        finished = false;
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
        createCanvasBuffer();
        createCanvaShader();
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

        viewport.TopLeftX = 0.f;
        viewport.TopLeftY = 0.f;
        viewport.Width = w;
        viewport.Height = h;
        viewport.MinDepth = D3D11_MIN_DEPTH;
        viewport.MaxDepth = D3D11_MAX_DEPTH;
        // RECT rect = {0,0,static_cast<LONG>(w),static_cast<LONG>(h)};
        // SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
    }

    void WinChronosWindow::displayOffscreen(Texture2D * rt){
        ChronosD3D11Texture2D* ct = dynamic_cast<ChronosD3D11Texture2D*>(rt);
        if(ct == nullptr){
            Panic(L"fatal");
        }
        sceneTexture = ct->getSRV();
    }

    void WinChronosWindow::draw() {
        if(sceneTexture == nullptr){
            Panic(L"fatal");
        }
        UINT stride = sizeof(float)*5;
        UINT offset = 0;
        
        deviceContext->RSSetViewports(1, &viewport);
        deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), NULL);
        float color[] = {0.0f,0.0f,1.0f,1.f};
        deviceContext->ClearRenderTargetView(rtv.Get(), color);
        deviceContext->IASetInputLayout(inputLayout.Get());
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext->IASetVertexBuffers(0, 1, verticesBuffer.GetAddressOf(), &stride, &offset);
        deviceContext->VSSetShader(vs.Get(), NULL, 0);
        deviceContext->PSSetShader(ps.Get(), NULL, 0);
        deviceContext->PSSetShaderResources(0, 1, &sceneTexture);
        deviceContext->PSSetSamplers(0, 1, sampler.GetAddressOf());
        deviceContext->Draw(6, 0);
        deviceContext->ClearState();
        ThrowIfFailed(swapChain->Present(1, 0));
    }

    std::vector<IOEvent> WinChronosWindow::processEvent(){
        std::vector<IOEvent> result;
        MSG msg;
        while (::PeekMessage(&msg, hWnd, 0U, 0U, PM_REMOVE)) {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);

            // if (msg.message == WM_QUIT){
            //     finished = true;
            //     break;
            // }

            switch (msg.message) {
                case WM_MOUSEMOVE:{
                    int x = LOWORD(msg.lParam);
                    int y = HIWORD(msg.lParam);
                    IOEvent e;
                    e.eventType = MOUSE_MOVE;
                    e.detail.xy={.x = x,.y = y};
                    result.push_back(e);
                    break;
                }
                case WM_LBUTTONDOWN:{
                    IOEvent e;
                    e.eventType = KEY_PRESSED;
                    e.detail.key = CHVK_LBUTTON;
                    result.push_back(e);
                    break;
                }
                case WM_LBUTTONUP:{
                    IOEvent e;
                    e.eventType = kEY_RELEASED;
                    e.detail.key = CHVK_LBUTTON;
                    result.push_back(e);
                    break;
                }
                case WM_KEYUP:{
                    IOEvent e;
                    e.eventType = kEY_RELEASED;
                    e.detail.key = (VirtualKey)msg.wParam;
                    result.push_back(e);
                    break;
                }
                case WM_KEYDOWN:{
                    IOEvent e;
                    e.eventType = KEY_PRESSED;
                    e.detail.key = (VirtualKey)msg.wParam;
                    result.push_back(e);
                    break;
                }
                default:
                break;
            }
        }
        if(finished) {
            IOEvent e;
            e.eventType = QUIT;
            result.push_back(e);
        }
        return result;
    }

    void WinChronosWindow::persent() {
            draw();
    }

    void WinChronosWindow::createCanvasBuffer(){
        float vertices[] = {
            -1.f,-1.f,0,0,1.f,
            1.f,1.f,0,1.f,0.f,
            1.f,-1.f,0,1.f,1.f,

            -1.f,-1.f,0,0,1.f,
            -1.f,1.f,0,0,0.f,
            1.f,1.f,0,1.f,0.f,
        };
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc,sizeof(desc));
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
        desc.ByteWidth = sizeof(vertices);
        desc.Usage = D3D11_USAGE_DEFAULT;
        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd,sizeof(sd));
        sd.pSysMem = vertices;
        ThrowIfFailed(d3d11Device->CreateBuffer(&desc, &sd, verticesBuffer.GetAddressOf()));
    }
    void WinChronosWindow::createCanvaShader(){
        std::vector<unsigned char> vbuffer =readDataFromFile("resources/shader/d3d11/basic_vert.cso");
        ThrowIfFailed(d3d11Device->CreateVertexShader(vbuffer.data()
            , vbuffer.size(),NULL,vs.GetAddressOf()));

        std::vector<unsigned char> pbuffer =readDataFromFile("resources/shader/d3d11/basic_pixel.cso");
        ThrowIfFailed(d3d11Device->CreatePixelShader(pbuffer.data()
            , pbuffer.size(),NULL,ps.GetAddressOf()));
        const D3D11_INPUT_ELEMENT_DESC basicVertexLayoutDesc[] =
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,3*sizeof(float),D3D11_INPUT_PER_VERTEX_DATA,0}
            };

        ThrowIfFailed(
            d3d11Device->CreateInputLayout(
                basicVertexLayoutDesc,
                ARRAYSIZE(basicVertexLayoutDesc),
                vbuffer.data(),
                vbuffer.size(),
                inputLayout.GetAddressOf()
                )
            );
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

        D3D11_SAMPLER_DESC samplerDesc;
        ZeroMemory(&samplerDesc, sizeof(samplerDesc));

        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

        // The sampler does not use anisotropic filtering, so this parameter is ignored.
        samplerDesc.MaxAnisotropy = 0;

        // Specify how texture coordinates outside of the range 0..1 are resolved.
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

        // Use no special MIP clamping or bias.
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        // Don't use a comparison function.
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

        // Border address mode is not used, so this parameter is ignored.
        samplerDesc.BorderColor[0] = 0.0f;
        samplerDesc.BorderColor[1] = 0.0f;
        samplerDesc.BorderColor[2] = 0.0f;
        samplerDesc.BorderColor[3] = 0.0f;

        ComPtr<ID3D11SamplerState> sampler;
        ThrowIfFailed(
            d3d11Device->CreateSamplerState(
                &samplerDesc,
                &sampler
            )
        );
        this->sampler = sampler;

    }

    void WinChronosWindow::quit() {
        finished = true;
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
            // ::PostQuitMessage(0);
            wcw->quit();
            return 0;
        }
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    void WinChronosWindow::captureCursor(){//todo
        // SetCapture(hWnd);
        RECT tmp;
        GetWindowRect(hWnd,&tmp);
        ClipCursor(&tmp);
        cursorCapture = true;
    }
    void WinChronosWindow::releaseCursor(){
        ReleaseCapture();
        cursorCapture = false;
    }
}