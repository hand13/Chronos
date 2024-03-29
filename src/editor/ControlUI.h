#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <render/Renderer.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;
namespace Chronos {
class ControlUI {
   private:
    bool finished;
    bool cleaned;
    ComPtr<ID3D11Device> device;
    ComPtr<ID3D11RenderTargetView> rtv;
    ComPtr<ID3D11DeviceContext> deviceContext;
    ComPtr<IDXGISwapChain> swapChain;
    HWND hWnd;
    WNDCLASSEX wc;
    UINT resizeWidth;
    UINT resizeHeight;
    bool createSwapChain();

   protected:
    virtual void showWindow() = 0;
    virtual void cleanResource();
    virtual void processMsg(const MSG& msg) = 0;

   public:
    ControlUI();
    void init(Renderer* renderer);
    void runInLoop();
    void quit();
    void show();
    bool createRTV();
    bool isStop();
    IDXGISwapChain* getSwapChain() { return swapChain.Get(); }
    ComPtr<ID3D11Device> shareDevice() { return device; }
    ComPtr<ID3D11DeviceContext> shareDeviceContext() { return deviceContext; }

    ID3D11Device* getDevice() { return device.Get(); }
    void setResizeWidth(UINT width) { resizeWidth = width; }
    void setResizeHeight(UINT height) { resizeHeight = height; }
    ID3D11DeviceContext* getDeviceContext() { return deviceContext.Get(); }
    virtual ~ControlUI();
};
}  // namespace Chronos