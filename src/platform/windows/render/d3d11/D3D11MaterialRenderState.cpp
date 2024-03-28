#include "D3D11MaterialRenderState.h"

#include <engine/ChronosEngine.h>
#include <engine/ResourceLoader.h>

#include <memory>

#include "platform/windows/render/d3d11/ChronosD3D11Texture2D.h"
#include "render/RenderConstantData.h"
#include "render/ShaderConfig.h"

namespace Chronos {

D3D11MaterialRenderState::D3D11MaterialRenderState(D3D11Renderer* renderer,
                                                   Material* material) {
    this->renderer = renderer;
    this->material = material;
}

void D3D11MaterialRenderState::update() {
    ResourceLoader* rl = Engine->getResourceLoader();
    ShaderConfig* sc = material->getShaderConfig();
    ps = std::dynamic_pointer_cast<ChronosPixelShader>(
        rl->loadShader(sc->getShaderName(), sc->getShaderType(), true));
    createConstantBufferAndTextures();
}
void D3D11MaterialRenderState::applyWith(const RenderConstantData& rcd) {
    updateConstantBuffer(rcd);
    updateTextures(rcd);
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    dc->PSSetShader(ps->getShader(), NULL, 0);

    useConstantBuffer();
    useTextures();
}
void D3D11MaterialRenderState::createConstantBufferAndTextures() {
    ShaderConfig* sc = material->getShaderConfig();
    for (auto& def : sc->getConstantDataDef()) {
        if (def.type == CDT_Texture2D) {
            textures[def.slot] = nullptr;
        } else {
            pixelConstantBuffers[def.slot] = renderer->createConstantBuffer(
                D3D11Renderer::span16(static_cast<u16>(def.size)));
        }
    }
}

void D3D11MaterialRenderState::updateConstantBuffer(
    const RenderConstantData& rcd) {
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    const RawDataMap& rdm = rcd.getMaterialDataMap();

    // if(rdm.size() != pixelConstantBuffers.size()){
    //     Panic("should not happended");
    // }

    for (auto& cd : rdm) {
        u8 slot = cd.second.slot;
        if (pixelConstantBuffers.find(slot) == pixelConstantBuffers.end()) {
            Panic("should not happended");
        }
        const RawData* rd = cd.second.rawData.get();
        ID3D11Buffer* cb = pixelConstantBuffers[slot].Get();
        if (cb == nullptr) {
            Panic("should not happended");
        }
        dc->UpdateSubresource(cb, 0, 0, rd->getConstantData(),
                              static_cast<UINT>(rd->getSize()), 0);
    }
}

void D3D11MaterialRenderState::updateTextures(const RenderConstantData& rcd) {
    const Texture2DMap& tm = rcd.getTextureMap();
    for (auto& st : tm) {
        if (textures.find(st.second.slot) == textures.end()) {
            Panic("should not happended");
        }
        textures[st.second.slot] =
            std::dynamic_pointer_cast<ChronosD3D11Texture2D>(st.second.texture);
    }
}

void D3D11MaterialRenderState::useConstantBuffer() {
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    for (auto& cb : pixelConstantBuffers) {
        dc->PSSetConstantBuffers(cb.first, 1, cb.second.GetAddressOf());
    }
}
void D3D11MaterialRenderState::useTextures() {
    ID3D11DeviceContext* dc = renderer->getDeviceContext();
    for (auto& st : textures) {
        if (st.second != nullptr) {
            ID3D11ShaderResourceView* srv = st.second->getSRV();
            dc->PSSetShaderResources(st.first, 1, &srv);
        }
    }
}

D3D11MaterialRenderState::~D3D11MaterialRenderState() {}
}  // namespace Chronos