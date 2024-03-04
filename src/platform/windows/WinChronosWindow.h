#include "../../ChronosWindow.h"
#include <Windows.h>
#include <minwindef.h>
#include <rpcndr.h>
#include <vector>
#include <windef.h>
#include <winuser.h>
#include <dxgi.h>
#include <d3d11.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

namespace Chronos {
    class WinChronosWindow :public ChronosWindow{
        private:
        ComPtr<ID3D11Device> d3d11Device;
        ComPtr<ID3D11DeviceContext> deviceContext;
        ComPtr<IDXGISwapChain> swapChain;
        ComPtr<ID3D11RenderTargetView> rtv;

        ComPtr<ID3D11Buffer> verticesBuffer;
        ComPtr<ID3D11PixelShader> ps;
        ComPtr<ID3D11VertexShader> vs;
        ComPtr<ID3D11InputLayout> inputLayout;
        ComPtr<ID3D11SamplerState> sampler;

        ID3D11ShaderResourceView* sceneTexture;
        D3D11_VIEWPORT viewport;

        WNDCLASSEX wc;
        HWND hWnd;
        unsigned int width;
        unsigned int height;

        boolean cursorCapture;
        boolean finished;

        public:
        WinChronosWindow();
        void createSwapChain();
        void createRenderTargetView();
        void quit();
        void resize(WPARAM wParam,unsigned int w,unsigned int h);
        virtual void getSize(unsigned int & w,unsigned int & h)override;
        virtual void init(Renderer * renderer) override;
        virtual void show() override;
        virtual std::vector<IOEvent> processEvent()override;
        virtual void persent() override;
        virtual void displayOffscreen(Texture2D * rt)override;
        void draw();
        inline ComPtr<ID3D11Device> shareDeivce(){
            return d3d11Device;
        }
        inline ComPtr<ID3D11DeviceContext> shareDeviceContext(){
            return deviceContext;
        }

        virtual void captureCursor()override;
        virtual void releaseCursor()override;

        virtual ~WinChronosWindow() override;
        private:

        void createCanvasBuffer();
        void createCanvaShader();

    };
}