#pragma once
#include "../RenderState.h"
#include "D3D11Renderer.h"
#include "common.h"
#include <d3d11.h>
#include <wrl/client.h>
namespace Chronos{
    class D3D11MeshRenderState:public RenderState{
        private:
        D3D11Renderer * render;
        Mesh * mesh;
        bool dirty;

        ComPtr<ID3D11Buffer> verticeBuffer;
        ComPtr<ID3D11InputLayout> inputLayout;
        ComPtr<ID3D11VertexShader> vertexShader;
        ComPtr<ID3D11PixelShader> pixelShader;//for tmp

        public:
        D3D11MeshRenderState(D3D11Renderer * render,Mesh * mesh);
        virtual void setDirty(bool dirty)override;
        virtual bool isDirty()override;
        virtual void update()override;
        virtual void apply()override;
        virtual ~D3D11MeshRenderState(){}
    };
}