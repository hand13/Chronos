#pragma once
#include <render/RenderState.h>
#include "ChronosPixelShader.h"
#include "ChronosD3D11Texture2D.h"
#include "D3D11Renderer.h"
#include "D3D11BaseRenderState.h"
#include "render/Material.h"
#include "render/RenderConstantData.h"
namespace Chronos{
    class D3D11MaterialRenderState :public D3D11BaseRenderState{
        private:
        D3D11Renderer * renderer;
        Material * material;
        std::shared_ptr<ChronosPixelShader> ps;
        std::map<u8, ComPtr<ID3D11Buffer>> pixelConstantBuffers;//slot,buffer
        std::map<u8,std::shared_ptr<ChronosD3D11Texture2D>> textures;
        public:
        D3D11MaterialRenderState(D3D11Renderer * renderer,Material * material);
        virtual void update()override;
        virtual void applyWith(const RenderConstantData& rcd)override;

        void createConstantBufferAndTextures();

        void updateConstantBuffer(const RenderConstantData& rcd);
        void updateTextures(const RenderConstantData& rcd);

        void useConstantBuffer();
        void useTextures();

        virtual ~D3D11MaterialRenderState();
    };
}