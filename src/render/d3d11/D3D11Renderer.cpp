#include "D3D11Renderer.h"
#include "../../Chronos.h"
#include "../../platform/windows/WinChronosWindow.h"
#include "../../Utils.h"
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <exception>
#include <memory>
#include <minwinbase.h>
#include <utility>
#include <wrl/client.h>
#include "ChronosD3D11RenderTarget.h"
#include "D3D11BaseRenderState.h"
#include "common.h"
namespace Chronos{

    D3D11Renderer::D3D11Renderer() {
        rtForRender = nullptr;
    }

    void D3D11Renderer::init(){
        WinChronosWindow * wc = dynamic_cast<WinChronosWindow*>(Chronos::INSTANCE->getWindow());
        if(wc == nullptr){
            Panic(L"fatal");
        }
        device = wc->shareDeivce();
        deviceContext = wc->shareDeviceContext();
        createRasterizeState();
        fm.init(device, deviceContext);
        createCBuffer();
        currentContext = nullptr;
        ZeroMemory(&viewport,sizeof(viewport));
    }

    void D3D11Renderer::createDefaultDevice(ID3D11Device** device,ID3D11DeviceContext** deviceContext){
    }

    void D3D11Renderer::createDefaultRenderTarget(ID3D11RenderTargetView** rtv){

    }
    void D3D11Renderer::setRenderContext(RenderContext * rct){
        currentContext = rct;
        RenderTarget * rt = currentContext->getRenderTarget();
        rtForRender = dynamic_cast<ChronosD3D11RenderTarget*>(rt);
        viewport =  genViewport(*rct->getCamera());
    }

    D3D11_VIEWPORT D3D11Renderer::genViewport(const Camera& camera){

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
        ZeroMemory(&bdesc,sizeof(bdesc));
        bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdesc.Usage = D3D11_USAGE_DEFAULT;
        bdesc.ByteWidth = sizeof(CameraBuffer);
        ThrowIfFailed(device->CreateBuffer(&bdesc, nullptr,cbuffer.GetAddressOf()));
    }

    void D3D11Renderer::beginRender() {
        deviceContext->RSSetViewports(1, &viewport);
        float color[] = {0.0f,0.f,0.0f,1.f};

        {
            ID3D11RenderTargetView* rtv = rtForRender->getRTV();
            ID3D11RenderTargetView* innerRTV = rtForRender->getInnerRTV();

            if(currentContext->shouldUseFXAA()){
                deviceContext->OMSetRenderTargets(1, &innerRTV, NULL);
                deviceContext->ClearRenderTargetView(innerRTV, color);
            }else {
                deviceContext->OMSetRenderTargets(1, &rtv, NULL);
                deviceContext->ClearRenderTargetView(rtv, color);
            }

        }

        deviceContext->RSSetState(rasterizeState.Get());
        Camera* camera = currentContext->getCamera();
        CameraBuffer cameraBuffer = camera->getCameraBuffer();
        deviceContext->UpdateSubresource(cbuffer.Get(), 0, 0, &cameraBuffer,sizeof(cameraBuffer),0);
        deviceContext->VSSetConstantBuffers(0, 1, cbuffer.GetAddressOf());
    }

    void D3D11Renderer::renderObject(RenderableObject * mesh){
    }

    void D3D11Renderer::renderBaseRenderableObject(BaseRenderableObject* robj){

        if(robj->getRenderState() == nullptr){
            robj->initRenderState(std::make_unique<D3D11BaseRenderState>(this,robj));
            robj->setDirty(true);
        }
        if(robj->getRenderState()->isDirty()){
            robj->getRenderState()->update();
        }
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        RenderState* rs = robj->getRenderState();
        rs->apply();

    }

    void D3D11Renderer::endRender() {
        deviceContext->ClearState();
        if(currentContext->shouldUseFXAA()){
            fm.apply(this->currentContext);
        }
        rtForRender = nullptr;
        currentContext = nullptr;
    }

    void D3D11Renderer::createRasterizeState(){
        D3D11_RASTERIZER_DESC rdesc;
        ZeroMemory(&rdesc,sizeof(rdesc));
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

    void D3D11Renderer::createRenderTargetView(const SizeU& size,ID3D11RenderTargetView** rtv,ID3D11ShaderResourceView ** rsv){
        ComPtr<ID3D11Texture2D> pBackBuffer;
        CD3D11_TEXTURE2D_DESC tdesc(DXGI_FORMAT_R8G8B8A8_UNORM,size.width,size.height);
        tdesc.BindFlags =D3D11_BIND_RENDER_TARGET |D3D11_BIND_SHADER_RESOURCE;
        tdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        D3D11_SUBRESOURCE_DATA sub;
        ZeroMemory(&sub,sizeof(sub));
        ThrowIfFailed(device->CreateTexture2D(&tdesc,NULL,pBackBuffer.GetAddressOf()));
        ThrowIfFailed(device->CreateRenderTargetView(pBackBuffer.Get(), NULL,rtv));

        D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
        ZeroMemory(&srvd,sizeof(srvd));
        srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvd.ViewDimension= D3D11_SRV_DIMENSION_TEXTURE2D;
        srvd.Texture2D.MipLevels = 1;
        ThrowIfFailed(device->CreateShaderResourceView(pBackBuffer.Get(), &srvd,rsv));
        // std::unique_ptr<ChronosD3D11Texture2D> texture = std::make_unique<ChronosD3D11Texture2D>();
        // result->setTexture(std::move(texture));
    }
    std::unique_ptr<RenderTarget> D3D11Renderer::createRenderTarget(const SizeU& size){
        std::unique_ptr<ChronosD3D11RenderTarget> result = std::make_unique<ChronosD3D11RenderTarget>();

        ComPtr<ID3D11RenderTargetView> rtv;
        ComPtr<ID3D11ShaderResourceView> rsv;
        createRenderTargetView(size, rtv.ReleaseAndGetAddressOf(),rsv.ReleaseAndGetAddressOf());
        std::unique_ptr<ChronosD3D11Texture2D> texture = std::make_unique<ChronosD3D11Texture2D>();
        texture->setSRV(rsv);
        result->setRTV(rtv);
        result->setTexture(std::move(texture));

        ComPtr<ID3D11RenderTargetView> innerRTV;
        ComPtr<ID3D11ShaderResourceView> innerRSV;
        createRenderTargetView(size, innerRTV.ReleaseAndGetAddressOf(),innerRSV.ReleaseAndGetAddressOf());
        std::unique_ptr<ChronosD3D11Texture2D> innertexture = std::make_unique<ChronosD3D11Texture2D>();
        innertexture->setSRV(innerRSV);

        result->setInnerRTV(innerRTV);
        result->setInnerTexture(std::move(innertexture));

        return result;

    }

    std::shared_ptr<Shader> D3D11Renderer::loadShader(const std::string& name,ShaderType shaderType,void * exdata,size_t exdataSize){
        std::shared_ptr<Shader> result;
        std::string path = shaderDir + "/" + name + ".cso";
        switch (shaderType) {
            case VERTEX_SHADER:{
                ComPtr<ID3D11VertexShader> vertexShader;
                ComPtr<ID3D11InputLayout> inputLayout;
                std::vector<unsigned char> vbuffer =readDataFromFile(path.c_str());
                ThrowIfFailed(device->CreateVertexShader(vbuffer.data()
                    , vbuffer.size(),NULL,vertexShader.GetAddressOf()));
                D3D11_INPUT_ELEMENT_DESC * desc = reinterpret_cast<D3D11_INPUT_ELEMENT_DESC*>(exdata);
                size_t elementSize = exdataSize/sizeof(D3D11_INPUT_ELEMENT_DESC);
                ThrowIfFailed(
                    device->CreateInputLayout(
                        desc,
                        static_cast<UINT>(elementSize),
                        vbuffer.data(),
                        vbuffer.size(),
                        inputLayout.GetAddressOf())
                    );
                result = std::make_shared<ChronosVertexShader>(vertexShader,inputLayout);
            }
            break;
            case PIXEL_SHADER:{
                ComPtr<ID3D11PixelShader> pixelShader;
                std::vector<unsigned char> pbuffer =readDataFromFile(path.c_str());
                ThrowIfFailed(device->CreatePixelShader(pbuffer.data()
                    , pbuffer.size(),NULL,pixelShader.GetAddressOf()));
                result = std::make_shared<ChronosPixelShader>(pixelShader);
            }
            break;
        }
        return result;
    }
    std::shared_ptr<Texture> D3D11Renderer::loaderTexture(const std::string& path,TextureParameter tparam){
        throw std::exception("todo");
    }
    D3D11Renderer::~D3D11Renderer(){
    }
}