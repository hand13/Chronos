#pragma once
#include <d3d11.h>
#include <platform/windows/windows_common.h>
#include <render/RenderState.h>
#include <render/VertexData.h>
#include <wrl/client.h>

#include "D3D11BaseRenderState.h"
#include "D3D11Renderer.h"
#include "render/VertexData.h"

namespace Chronos {
class D3D11VertexDataRenderState : public D3D11BaseRenderState {
   private:
    D3D11Renderer* render;
    VertexData* robj;
    ComPtr<ID3D11Buffer> verticeBuffer;
    ComPtr<ID3D11Buffer> indicesBuffer;

   public:
    D3D11VertexDataRenderState(D3D11Renderer* render, VertexData* robj);
    virtual void update() override;
    virtual void applyWith(const RenderConstantData& rcd) override;
    virtual ~D3D11VertexDataRenderState();
};
}  // namespace Chronos