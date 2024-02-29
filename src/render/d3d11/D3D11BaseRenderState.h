#pragma once
#include "../RenderState.h"
#include "D3D11Renderer.h"
#include "common.h"
#include <d3d11.h>
#include <vector>
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
        ComPtr<ID3D11Buffer> indicesBuffer;
        std::shared_ptr<ChronosVertexShader> vs;
        std::shared_ptr<ChronosPixelShader> ps;


        std::vector<ComPtr<ID3D11Buffer>> vertParamConstantBuffers;
        std::vector<ComPtr<ID3D11Buffer>> pixelParamConstantBuffers;

        void createBufferForShaderParams();
        void transferParamsToConstantBuffers();
        void applyShaderParamConstantBuffers();

        ComPtr<ID3D11Buffer> createConstantBuffer(size_t size);

        public:
        D3D11BaseRenderState(D3D11Renderer * render,BaseRenderableObject * robj);
        virtual void setDirty(bool dirty)override;
        virtual bool isDirty()override;
        virtual void update()override;
        virtual void apply()override;
        virtual ~D3D11BaseRenderState(){}
        static std::vector<D3D11_INPUT_ELEMENT_DESC> genInputElementDescFromAttrSet(Geometry::AttributeSet* as);
    };
}