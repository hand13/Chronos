#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "../Renderer.h"
#include "../RenderContext.h"
using Microsoft::WRL::ComPtr;
namespace Chronos {
    class D3D11Renderer:public Renderer{
        private:

        ComPtr<ID3D11Device> deivice;
        ComPtr<ID3D11DeviceContext> deviceContext;
        RenderContext * currentContext;
        ID3D11RenderTargetView * currentRTV;
        D3D11_VIEWPORT viewport;

        public:
        virtual void init()override;
        virtual void beginRender()override;
        virtual void endRender()override;
        void createDefaultDevice(ID3D11Device** device,ID3D11DeviceContext** deviceContext);
        void createDefaultRenderTarget(ID3D11RenderTargetView** rtv);
        virtual void setRenderContext(RenderContext * rct)override;
        virtual void renderObject(RenderableObject * robj)override;
        D3D11_VIEWPORT genViewport(const Camera& cmamea);
        virtual std::unique_ptr<RenderTarget> createRenderTarget()override;
        virtual ~D3D11Renderer();
    };
};