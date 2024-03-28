#include "D3D11Renderer.h"

#include <WICTextureLoader.h>
#include <base/Log.h>
#include <base/StringHelper.h>
#include <base/Utils.h>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <minwinbase.h>
#include <wrl/client.h>

#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "ChronosD3D11RenderTarget.h"
#include "ChronosD3D11Texture2D.h"
#include "ChronosPixelShader.h"
#include "ChronosVertexShader.h"
#include "D3D11VertexDataRenderState.h"
#include "D3D11VertexProcRenderState.h"
#include "platform/windows/render/d3d11/D3D11MaterialRenderState.h"
#include "platform/windows/windows_common.h"
#include "render/RenderState.h"

namespace Chronos {

D3D11Renderer::D3D11Renderer() { rtForRender = nullptr; }

void D3D11Renderer::init() {
    createDevice();
    createRasterizeState();
    fm.init(device, deviceContext);
    createCBuffer();
    currentContext = nullptr;
    ZeroMemory(&viewport, sizeof(viewport));
    createSamplerState(samplerState.GetAddressOf());
}

void D3D11Renderer::createDevice() {
    createDefaultDevice(device.GetAddressOf(), deviceContext.GetAddressOf());
}

void D3D11Renderer::createDefaultDevice(ID3D11Device** device,
                                        ID3D11DeviceContext** deviceContext) {
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    ThrowIfFailed(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flags,
                                    &featureLevel, 1, D3D11_SDK_VERSION, device,
                                    NULL, deviceContext));
}

void D3D11Renderer::createDefaultRenderTarget(ID3D11RenderTargetView** rtv) {}

void D3D11Renderer::setRenderContext(RenderContext* rct) {
    currentContext = rct;
    RenderTarget* rt = currentContext->getRenderTarget();
    rtForRender = dynamic_cast<ChronosD3D11RenderTarget*>(rt);
    viewport = genViewport(*rct->getCamera());
}

D3D11_VIEWPORT D3D11Renderer::genViewport(const Camera& camera) {
    D3D11_VIEWPORT dv;
    dv.TopLeftX = 0.f;
    dv.TopLeftY = 0.f;
    dv.Width = static_cast<float>(camera.getWidth());
    dv.Height = static_cast<float>(camera.getHeight());
    dv.MinDepth = D3D11_MIN_DEPTH;
    dv.MaxDepth = D3D11_MAX_DEPTH;
    return dv;
}

void D3D11Renderer::createCBuffer() {
    D3D11_BUFFER_DESC bdesc;
    ZeroMemory(&bdesc, sizeof(bdesc));
    bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bdesc.Usage = D3D11_USAGE_DEFAULT;
    bdesc.ByteWidth = sizeof(CameraBuffer);
    ThrowIfFailed(
        device->CreateBuffer(&bdesc, nullptr, cbuffer.GetAddressOf()));
}

void D3D11Renderer::beginRender() {
    deviceContext->RSSetViewports(1, &viewport);
    float color[] = {0.0f, 0.f, 0.0f, 1.f};

    {
        ID3D11RenderTargetView* rtv = rtForRender->getRTV();
        ID3D11RenderTargetView* innerRTV = rtForRender->getInnerRTV();
        ID3D11DepthStencilView* dsv = rtForRender->getDSV();

        if (currentContext->shouldUseFXAA()) {
            deviceContext->OMSetRenderTargets(1, &innerRTV, dsv);
            deviceContext->ClearRenderTargetView(innerRTV, color);
        } else {
            deviceContext->OMSetRenderTargets(1, &rtv, dsv);
            deviceContext->ClearRenderTargetView(rtv, color);
        }

        deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
    }

    deviceContext->RSSetState(rasterizeState.Get());
    Camera* camera = currentContext->getCamera();
    CameraBuffer cameraBuffer = camera->getCameraBuffer();
    deviceContext->UpdateSubresource(cbuffer.Get(), 0, 0, &cameraBuffer,
                                     sizeof(cameraBuffer), 0);
    deviceContext->VSSetConstantBuffers(0, 1, cbuffer.GetAddressOf());
    deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());
}

void D3D11Renderer::createOrUpdateRenderState(
    RenderStateHolder& rsh, std::unique_ptr<RenderState>&& rs) {
    RenderState* irs = rsh.getRenderstate();
    if (irs == nullptr) {
        rsh.setRenderState(std::move(rs));
        irs = rsh.getRenderstate();
        irs->setDirty(true);
    }
    if (irs->isDirty()) {
        irs->update();
    }
}

void D3D11Renderer::render(VertexData& vertexData, VertexProc& vertexProc,
                           Material& material, const RenderConstantData& rcd) {
    /**
     * @brief todo
     *
     */
    if (vertexData.getRenderstate() == nullptr) {
        createOrUpdateRenderState(
            vertexData,
            std::make_unique<D3D11VertexDataRenderState>(this, &vertexData));
    }
    if (vertexProc.getRenderstate() == nullptr) {
        createOrUpdateRenderState(
            vertexProc, std::make_unique<D3D11VertexProcRenderState>(
                            this, &vertexProc, vertexData.getAttributeSet()));
    }
    if (material.getRenderstate() == nullptr) {
        createOrUpdateRenderState(
            material,
            std::make_unique<D3D11MaterialRenderState>(this, &material));
    }

    vertexData.getRenderstate()->applyWith(rcd);
    vertexProc.getRenderstate()->applyWith(rcd);
    material.getRenderstate()->applyWith(rcd);

    if (vertexData.useIndices()) {
        deviceContext->DrawIndexed(
            static_cast<UINT>(vertexData.getIndices().size()), 0, 0);
    } else {
        deviceContext->Draw(static_cast<UINT>(vertexData.getVerticesCount()),
                            0);
    }
}

void D3D11Renderer::endRender() {
    deviceContext->ClearState();
    if (currentContext->shouldUseFXAA()) {
        fm.apply(this->currentContext);
    }
    rtForRender = nullptr;
    currentContext = nullptr;
}

void D3D11Renderer::createRasterizeState() {
    D3D11_RASTERIZER_DESC rdesc;
    ZeroMemory(&rdesc, sizeof(rdesc));
    rdesc.AntialiasedLineEnable = true;
    rdesc.CullMode = D3D11_CULL_BACK;
    rdesc.DepthBias = 0;
    rdesc.DepthBiasClamp = 0.0f;
    rdesc.DepthClipEnable = true;
    rdesc.FillMode = D3D11_FILL_SOLID;
    rdesc.FrontCounterClockwise = false;
    rdesc.MultisampleEnable = false;
    rdesc.ScissorEnable = false;
    rdesc.SlopeScaledDepthBias = 0.0f;
}

void D3D11Renderer::createDepthStencilView(const SizeU& size,
                                           ID3D11DepthStencilView** dsv) {
    D3D11_TEXTURE2D_DESC depthStencilDesc;
    depthStencilDesc.Width = size.width;
    depthStencilDesc.Height = size.height;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilDesc.CPUAccessFlags = 0;
    depthStencilDesc.MiscFlags = 0;
    ComPtr<ID3D11Texture2D> depthStencil;
    ThrowIfFailed(
        device->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencil));

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    depthStencilViewDesc.Format = depthStencilDesc.Format;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Flags = 0;
    depthStencilViewDesc.Texture2D.MipSlice = 0;
    ThrowIfFailed(device->CreateDepthStencilView(depthStencil.Get(),
                                                 &depthStencilViewDesc, dsv));
}

void D3D11Renderer::createRenderTargetView(const SizeU& size,
                                           ID3D11RenderTargetView** rtv,
                                           ID3D11ShaderResourceView** rsv) {
    ComPtr<ID3D11Texture2D> pBackBuffer;
    CD3D11_TEXTURE2D_DESC tdesc(DXGI_FORMAT_R8G8B8A8_UNORM, size.width,
                                size.height);
    tdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    tdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    D3D11_SUBRESOURCE_DATA sub;
    ZeroMemory(&sub, sizeof(sub));
    ThrowIfFailed(
        device->CreateTexture2D(&tdesc, NULL, pBackBuffer.GetAddressOf()));
    ThrowIfFailed(device->CreateRenderTargetView(pBackBuffer.Get(), NULL, rtv));

    D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
    ZeroMemory(&srvd, sizeof(srvd));
    srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srvd.Texture2D.MipLevels = 1;
    ThrowIfFailed(
        device->CreateShaderResourceView(pBackBuffer.Get(), &srvd, rsv));
    // std::unique_ptr<ChronosD3D11Texture2D> texture =
    // std::make_unique<ChronosD3D11Texture2D>();
    // result->setTexture(std::move(texture));
}
std::unique_ptr<RenderTarget> D3D11Renderer::createRenderTarget(
    const SizeU& size) {
    std::unique_ptr<ChronosD3D11RenderTarget> result =
        std::make_unique<ChronosD3D11RenderTarget>();

    ComPtr<ID3D11RenderTargetView> rtv;
    ComPtr<ID3D11ShaderResourceView> rsv;
    createRenderTargetView(size, rtv.ReleaseAndGetAddressOf(),
                           rsv.ReleaseAndGetAddressOf());
    std::unique_ptr<ChronosD3D11Texture2D> texture =
        std::make_unique<ChronosD3D11Texture2D>();
    texture->setSRV(rsv);
    result->setRTV(rtv);
    result->setTexture(std::move(texture));

    ComPtr<ID3D11RenderTargetView> innerRTV;
    ComPtr<ID3D11ShaderResourceView> innerRSV;
    createRenderTargetView(size, innerRTV.ReleaseAndGetAddressOf(),
                           innerRSV.ReleaseAndGetAddressOf());
    std::unique_ptr<ChronosD3D11Texture2D> innertexture =
        std::make_unique<ChronosD3D11Texture2D>();
    innertexture->setSRV(innerRSV);

    result->setInnerRTV(innerRTV);
    result->setInnerTexture(std::move(innertexture));

    ComPtr<ID3D11DepthStencilView> dsv;
    createDepthStencilView(size, dsv.ReleaseAndGetAddressOf());
    result->setDSV(dsv);
    return result;
}

std::shared_ptr<Shader> D3D11Renderer::loadShader(const std::string& name,
                                                  ShaderType shaderType,
                                                  void* exdata,
                                                  size_t exdataSize) {
    std::shared_ptr<Shader> result;
    std::string path = shaderDir + "/" + name + ".cso";
    switch (shaderType) {
        case VERTEX_SHADER: {
            ComPtr<ID3D11VertexShader> vertexShader;
            ComPtr<ID3D11InputLayout> inputLayout;
            std::vector<unsigned char> vbuffer = readDataFromFile(path.c_str());
            ThrowIfFailed(
                device->CreateVertexShader(vbuffer.data(), vbuffer.size(), NULL,
                                           vertexShader.GetAddressOf()));
            D3D11_INPUT_ELEMENT_DESC* desc =
                reinterpret_cast<D3D11_INPUT_ELEMENT_DESC*>(exdata);
            size_t elementSize = exdataSize / sizeof(D3D11_INPUT_ELEMENT_DESC);
            ThrowIfFailed(device->CreateInputLayout(
                desc, static_cast<UINT>(elementSize), vbuffer.data(),
                vbuffer.size(), inputLayout.GetAddressOf()));
            result = std::make_shared<ChronosVertexShader>(vertexShader,
                                                           inputLayout);
        } break;
        case PIXEL_SHADER: {
            ComPtr<ID3D11PixelShader> pixelShader;
            std::vector<unsigned char> pbuffer = readDataFromFile(path.c_str());
            ThrowIfFailed(
                device->CreatePixelShader(pbuffer.data(), pbuffer.size(), NULL,
                                          pixelShader.GetAddressOf()));
            result = std::make_shared<ChronosPixelShader>(pixelShader);
        } break;
    }
    return result;
}

std::shared_ptr<Texture2D> D3D11Renderer::loaderTexture2D(
    const std::string& path, const TextureParameter& tparam) {
    std::shared_ptr<ChronosD3D11Texture2D> result =
        std::make_shared<ChronosD3D11Texture2D>();
    std::wstring wp = UTF8toWide(path);
    ComPtr<ID3D11ShaderResourceView> rsv;
    ID3D11Resource* res;
    ThrowIfFailed(DirectX::CreateWICTextureFromFile(device.Get(), wp.c_str(),
                                                    &res, rsv.GetAddressOf()));
    if (!rsv) {
        Panic("load texture failed");
    }
    ID3D11Texture2D* t;
    ThrowIfFailed(res->QueryInterface(&t));
    D3D11_TEXTURE2D_DESC dtd = {};
    t->GetDesc(&dtd);
    result->setSRV(rsv);
    result->width = dtd.Width;
    result->height = dtd.Height;
    res->Release();
    t->Release();
    return result;
}

D3D11Renderer::~D3D11Renderer() { Log("d3d11 renderer destructed"); }

void D3D11Renderer::printLiveObject(ComPtr<ID3D11Device> device) {
    ID3D11Debug* debuger;
    HRESULT hr = device->QueryInterface(__uuidof(ID3D11Debug),
                                        reinterpret_cast<void**>(&debuger));
    if (SUCCEEDED(hr)) {
        hr = debuger->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    }
    if (debuger != nullptr) {
        debuger->Release();
    }
}

void D3D11Renderer::createSamplerState(ID3D11SamplerState** sampleState) {
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

    // The sampler does not use anisotropic filtering, so this parameter is
    // ignored.
    samplerDesc.MaxAnisotropy = 0;

    // Specify how texture coordinates outside of the range 0..1 are resolved.
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    // Use no special MIP clamping or bias.
    samplerDesc.MipLODBias = 0.0f;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // Don't use a comparison function.
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

    // Border address mode is not used, so this parameter is ignored.
    samplerDesc.BorderColor[0] = 0.0f;
    samplerDesc.BorderColor[1] = 0.0f;
    samplerDesc.BorderColor[2] = 0.0f;
    samplerDesc.BorderColor[3] = 0.0f;
    ThrowIfFailed(device->CreateSamplerState(&samplerDesc, sampleState));
}
std::vector<D3D11_INPUT_ELEMENT_DESC>
D3D11Renderer::genInputElementDescFromAttrSet(Geometry::AttributeSet* as) {
    std::vector<D3D11_INPUT_ELEMENT_DESC> result;
    for (const Geometry::Attribute& attr : as->getAttributes()) {
        const char* semantic = nullptr;
        DXGI_FORMAT format = DXGI_FORMAT_R32G32B32_FLOAT;
        if (attr.name == "pos") {
            semantic = "POSITION";
            format = DXGI_FORMAT_R32G32B32_FLOAT;
        } else if (attr.name == "uv") {
            semantic = "TEXCOORD";
            format = DXGI_FORMAT_R32G32_FLOAT;
        } else if (attr.name == "normal") {
            semantic = "NORMAL";
            format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        UINT offset = static_cast<UINT>(as->getAttributeOffset(attr.name));
        D3D11_INPUT_ELEMENT_DESC desc = {
            semantic, 0, format, 0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0};
        result.push_back(desc);
    }

    return result;
}
ComPtr<ID3D11Buffer> D3D11Renderer::createConstantBuffer(size_t size) {
    ComPtr<ID3D11Buffer> result;
    D3D11_BUFFER_DESC bdesc;
    ZeroMemory(&bdesc, sizeof(bdesc));
    bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bdesc.Usage = D3D11_USAGE_DEFAULT;
    bdesc.ByteWidth = static_cast<UINT>(size);
    ThrowIfFailed(device->CreateBuffer(&bdesc, nullptr, result.GetAddressOf()));
    return result;
}

u16 D3D11Renderer::span16(u16 size) {
    if ((size % MAX_PACK_SIZE) == 0) {
        return size;
    }
    return MAX_PACK_SIZE + size - (size % MAX_PACK_SIZE);
}
}  // namespace Chronos