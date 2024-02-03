#include "../../ChronosWindow.h"
#include <Windows.h>
#include <minwindef.h>
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

        ID3D11ShaderResourceView* sceneTexture;

        WNDCLASSEX wc;
        HWND hWnd;
        unsigned int width;
        unsigned int height;
        public:
        WinChronosWindow();
        void createD3D11DeviceAndSwapChain();
        void createRenderTargetView();
        void resize(WPARAM wParam,unsigned int w,unsigned int h);
        virtual void getSize(unsigned int & w,unsigned int & h)override;
        virtual void init() override;
        virtual void show() override;
        virtual bool processEvent()override;
        virtual void persent() override;
        virtual void displayOffscreen(Texture2D * rt)override;
        void draw();
        inline ComPtr<ID3D11Device> shareDeivce(){
            return d3d11Device;
        }
        inline ComPtr<ID3D11DeviceContext> shareDeviceContext(){
            return deviceContext;
        }
        private:

        void createCanvasBuffer();
        void createCanvaShader();

        virtual ~WinChronosWindow() override;
    };
}