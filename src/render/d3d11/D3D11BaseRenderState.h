#pragma once
#include "../RenderState.h"
#include "D3D11Renderer.h"
#include "common.h"
#include <d3d11.h>
#include <wrl/client.h>
#include "ChronosVertexShader.h"
#include "ChronosPixelShader.h"
namespace Chronos{
    class D3D11BaseRenderState:public RenderState{
        private:
        D3D11Renderer * render;
        BaseRenderableObject * robj;
        bool dirty;

        ComPtr<ID3D11Buffer> verticeBuffer;
        std::shared_ptr<ChronosVertexShader> vs;
        std::shared_ptr<ChronosPixelShader> ps;

        public:
        D3D11BaseRenderState(D3D11Renderer * render,BaseRenderableObject * robj);
        virtual void setDirty(bool dirty)override;
        virtual bool isDirty()override;
        virtual void update()override;
        virtual void apply()override;
        virtual ~D3D11BaseRenderState(){}
    };
}