#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "../RenderableObject.h"
#include "../RenderContext.h"
using Microsoft::WRL::ComPtr;
namespace Chronos {
    class D3D11Renderer{
        private:

        ComPtr<ID3D11Device> deivice;
        ComPtr<ID3D11DeviceContext> deviceContext;

        public:
        void init();
        void createDefaultDevice(ID3D11Device** device,ID3D11DeviceContext** deviceContext);
        void createDefaultRenderTarget(ID3D11RenderTargetView** rtv);
        virtual void setRenderContext(RenderContext * rct);
        virtual void render(RenderableObject * robj);
    };
};