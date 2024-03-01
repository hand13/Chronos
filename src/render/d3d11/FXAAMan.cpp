#include "FXAAMan.h"
#include "../../Utils.h"
#include <d3d11.h>
#include <minwindef.h>
#include <vector>
#include "D3D11Renderer.h"
namespace Chronos {
    void FXAAMan::init(ComPtr<ID3D11Device> device,ComPtr<ID3D11DeviceContext> deviceContext){
        this->device = device;
        this->deviceContext = deviceContext;
        createResource();
    }
    void FXAAMan::apply(RenderContext* rc){
        D3D11_VIEWPORT viewport = D3D11Renderer::genViewport(*rc->getCamera());
        ChronosD3D11RenderTarget *crt  =  dynamic_cast<ChronosD3D11RenderTarget*>(rc->getRenderTarget());

        ID3D11RenderTargetView * rt =   crt->getRTV();
        ID3D11ShaderResourceView * srv = dynamic_cast<ChronosD3D11Texture2D*>(crt->innerAsTexture())->getSRV();
        float rcpFrame[] = {1.f/static_cast<float>(viewport.Width),1.f/static_cast<float>(viewport.Height),0.f,0.f};
        deviceContext->UpdateSubresource(constBuffer.Get(), 0, 0, rcpFrame,sizeof(rcpFrame),0);

        deviceContext->RSSetViewports(1, &viewport);
        deviceContext->OMSetRenderTargets(1, &rt, NULL);
        float color[] = {0.0f,1.0f,0.0f,1.f};
        UINT stride = 5 * sizeof(float);
        UINT offset = 0;
        deviceContext->ClearRenderTargetView(rt, color);
        deviceContext->IASetInputLayout(inputLayout.Get());
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext->IASetVertexBuffers(0, 1, verticeBuffer.GetAddressOf(), &stride, &offset);
        deviceContext->VSSetShader(vs.Get(), NULL, 0);
        deviceContext->PSSetShader(ps.Get(), NULL, 0);
        deviceContext->PSSetShaderResources(0, 1, &srv);
        deviceContext->PSSetSamplers(0, 1, sampleState.GetAddressOf());
        deviceContext->PSSetConstantBuffers(0, 1, constBuffer.GetAddressOf());
        deviceContext->Draw(6, 0);
        deviceContext->ClearState();
    }
    void FXAAMan::createResource(){
        std::vector<float> vertice = {
            -1.f,-1.f,0,0,1.f,
            1.f,1.f,0,1.f,0.f,
            1.f,-1.f,0,1.f,1.f,

            -1.f,-1.f,0,0,1.f,
            -1.f,1.f,0,0,0.f,
            1.f,1.f,0,1.f,0.f,
        };
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc,sizeof(desc));
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
        desc.ByteWidth = static_cast<UINT>(vertice.size()*sizeof(float));
        desc.Usage = D3D11_USAGE_DEFAULT;
        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd,sizeof(sd));
        sd.pSysMem = vertice.data();

        ThrowIfFailed(device->CreateBuffer(&desc, &sd, verticeBuffer.GetAddressOf()));
        std::vector<unsigned char> vbuffer =readDataFromFile("resources/shader/d3d11/fxaa_vert.cso");
        ThrowIfFailed(device->CreateVertexShader(vbuffer.data()
            , vbuffer.size(),NULL,vs.GetAddressOf()));
        std::vector<unsigned char> pbuffer =readDataFromFile("resources/shader/d3d11/fxaa_pixel.cso");
        ThrowIfFailed(device->CreatePixelShader(pbuffer.data()
            , pbuffer.size(),NULL,ps.GetAddressOf()));
        const D3D11_INPUT_ELEMENT_DESC BaseVertexLayoutDesc[] =
            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,3*sizeof(float),D3D11_INPUT_PER_VERTEX_DATA,0}
            };
        ThrowIfFailed(
            device->CreateInputLayout(
                BaseVertexLayoutDesc,
                ARRAYSIZE(BaseVertexLayoutDesc),
                vbuffer.data(),
                vbuffer.size(),
                inputLayout.GetAddressOf())
        );

        D3D11_SAMPLER_DESC samplerDesc;
        ZeroMemory(&samplerDesc, sizeof(samplerDesc));
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        // The sampler does not use anisotropic filtering, so this parameter is ignored.
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
        ComPtr<ID3D11SamplerState> sampler;

        ThrowIfFailed(
            device->CreateSamplerState(
                &samplerDesc,
                &sampler
            )
        );
        this->sampleState = sampler;

        D3D11_BUFFER_DESC bdesc;
        ZeroMemory(&bdesc,sizeof(bdesc));
        bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdesc.Usage = D3D11_USAGE_DEFAULT;
        bdesc.ByteWidth = sizeof(float)*4;
        ThrowIfFailed(device->CreateBuffer(&bdesc, nullptr,constBuffer.GetAddressOf()));
    }
}
