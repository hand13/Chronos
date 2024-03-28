#include "D3D11VertexProcRenderState.h"

#include <engine/ChronosEngine.h>
#include <engine/ResourceLoader.h>

#include <cstddef>
#include <memory>
#include <vector>

#include "base/Utils.h"
#include "platform/windows/render/d3d11/ChronosVertexShader.h"
#include "platform/windows/render/d3d11/D3D11Renderer.h"
#include "render/AttributeSet.h"
#include "render/RenderConstantData.h"
#include "render/ShaderConfig.h"

namespace Chronos {
D3D11VertexProcRenderState::D3D11VertexProcRenderState(
    D3D11Renderer* renderer, VertexProc* vertexProc,
    Geometry::AttributeSet* as) {
    this->renderer = renderer;
    this->vertexProc = vertexProc;
    this->as = as;
}
void D3D11VertexProcRenderState::update() {
    ResourceLoader* rl = Engine->getResourceLoader();

    ShaderConfig* sc = vertexProc->getShaderConfig();
    std::vector<D3D11_INPUT_ELEMENT_DESC> eleDesc =
        D3D11Renderer::genInputElementDescFromAttrSet(as);
    vs = std::dynamic_pointer_cast<ChronosVertexShader>(rl->loadShader(
        sc->getShaderName(), sc->getShaderType(), true, eleDesc.data(),
        eleDesc.size() * sizeof(D3D11_INPUT_ELEMENT_DESC)));
    createConstantBuffer();
}

void D3D11VertexProcRenderState::applyWith(const RenderConstantData& rcd) {
    updateConstantBuffer(rcd);
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    dc->IASetInputLayout(vs->getInputLayout());
    dc->VSSetShader(vs->getShader(), NULL, 0);
    useConstantBuffer();
}

void D3D11VertexProcRenderState::createConstantBuffer() {
    ShaderConfig* sc = vertexProc->getShaderConfig();
    for (auto& def : sc->getConstantDataDef()) {
        vertexProcConstantBuffers[def.slot] = renderer->createConstantBuffer(
            D3D11Renderer::span16(static_cast<u16>(def.size)));
    }
}
void D3D11VertexProcRenderState::updateConstantBuffer(
    const RenderConstantData& rcd) {
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    const RawDataMap& rdm = rcd.getVertexProcDataMap();
    if (rdm.size() != vertexProcConstantBuffers.size()) {
        Panic("should not happended");
    }
    for (auto& cd : rdm) {
        u8 slot = cd.second.slot;
        if (vertexProcConstantBuffers.find(slot) ==
            vertexProcConstantBuffers.end()) {
            Panic("should not happended");
        }
        const RawData* rd = cd.second.rawData.get();
        ID3D11Buffer* cb = vertexProcConstantBuffers[slot].Get();
        if (cb == nullptr) {
            Panic("should not happended");
        }
        dc->UpdateSubresource(cb, 0, 0, rd->getConstantData(),
                              static_cast<UINT>(rd->getSize()), 0);
    }
}

void D3D11VertexProcRenderState::useConstantBuffer() {
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    for (auto& cb : vertexProcConstantBuffers) {
        dc->VSSetConstantBuffers(cb.first, 1, cb.second.GetAddressOf());
    }
}

D3D11VertexProcRenderState::~D3D11VertexProcRenderState() {}
}  // namespace Chronos