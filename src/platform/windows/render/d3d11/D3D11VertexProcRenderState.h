#pragma once
#include <render/RenderState.h>
#include <render/VertexProc.h>

#include "ChronosVertexShader.h"
#include "D3D11BaseRenderState.h"
#include "D3D11Renderer.h"
#include "render/AttributeSet.h"

namespace Chronos {
class D3D11VertexProcRenderState : public D3D11BaseRenderState {
   private:
    D3D11Renderer* renderer;
    VertexProc* vertexProc;
    Geometry::AttributeSet* as;

    std::shared_ptr<ChronosVertexShader> vs;
    std::map<u8, ComPtr<ID3D11Buffer>> vertexProcConstantBuffers;  // slot,buffer

   public:
    D3D11VertexProcRenderState(D3D11Renderer* renderer, VertexProc* vertexProc,
                               Geometry::AttributeSet* as);
    virtual void update() override;
    virtual void applyWith(const RenderConstantData& rcd) override;
    void createConstantBuffer();
    void updateConstantBuffer(const RenderConstantData& rcd);
    void useConstantBuffer();
    virtual ~D3D11VertexProcRenderState();
};
}  // namespace Chronos