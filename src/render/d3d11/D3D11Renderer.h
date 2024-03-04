#pragma once
#include <d3d11.h>
#include <rpcndr.h>
#include <wrl/client.h>
#include "../Renderer.h"
#include "../RenderContext.h"
#include "../BaseRenderableObject.h"
#include "ChronosD3D11RenderTarget.h"
#include "FXAAMan.h"
using Microsoft::WRL::ComPtr;
namespace Chronos {
    class D3D11Renderer:public Renderer{
        private:

        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> deviceContext;
        RenderContext * currentContext;
        ComPtr<ID3D11Buffer> cbuffer;
        ComPtr<ID3D11RasterizerState> rasterizeState;
        FXAAMan fm;

        D3D11_VIEWPORT viewport;
        ChronosD3D11RenderTarget * rtForRender;
        std::string shaderDir = CHRONOS_D3D11_SHADER_DIR;

        void createCBuffer();
        void createDevice();

        public:
        D3D11Renderer();
        virtual void init()override;
        virtual void beginRender()override;
        virtual void endRender()override;
        void createDefaultDevice(ID3D11Device** device,ID3D11DeviceContext** deviceContext);
        virtual std::shared_ptr<Shader> loadShader(const std::string& name,ShaderType shaderType,void * exdata,size_t exdataSize)override;
        virtual std::shared_ptr<Texture> loaderTexture(const std::string& path,TextureParameter tparam)override;
        void createDefaultRenderTarget(ID3D11RenderTargetView** rtv);
        void applyFxaa();
        void createRasterizeState();

        inline ID3D11Device* getDevice(){
            return device.Get();
        }

        inline ID3D11DeviceContext* getDeviceContext(){
            return deviceContext.Get();
        }

        inline ComPtr<ID3D11Device> shareDevice(){
            return device;
        }
        inline ComPtr<ID3D11DeviceContext> shareDeviceCOntext(){
            return deviceContext;
        }
        virtual void setRenderContext(RenderContext * rct)override;

        virtual void renderObject(RenderableObject * robj)override;
        virtual void renderBaseRenderableObject(BaseRenderableObject * robj)override;

        /**
        * @brief 
        * depth from 0 to 1
        * @param cmamea 
        * @return D3D11_VIEWPORT 
        */

        static D3D11_VIEWPORT genViewport(const Camera& cmamea);
        virtual std::unique_ptr<RenderTarget> createRenderTarget(const SizeU& size)override;
        void createRenderTargetView(const SizeU& size,ID3D11RenderTargetView** rtv,ID3D11ShaderResourceView ** rsv);
        void createDepthStencilView(const SizeU& size,ID3D11DepthStencilView** dsv);
        virtual ~D3D11Renderer();
    };
};