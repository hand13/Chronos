#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "../Renderer.h"
#include "../RenderContext.h"
#include "../Mesh.h"
using Microsoft::WRL::ComPtr;
namespace Chronos {
    class D3D11Renderer:public Renderer{
        private:

        ComPtr<ID3D11Device> device;
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

        ID3D11Device* getDevice(){
            return device.Get();
        }

        ID3D11DeviceContext* getDeviceContext(){
            return deviceContext.Get();
        }
        virtual void setRenderContext(RenderContext * rct)override;

        virtual void renderObject(RenderableObject * robj)override;
        virtual void renderMesh(Mesh* mesh)override;

        D3D11_VIEWPORT genViewport(const Camera& cmamea);
        virtual std::unique_ptr<RenderTarget> createRenderTarget()override;
        virtual ~D3D11Renderer();
    };
};