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
#include <wrl/client.h>
#include "ChronosD3D11RenderTarget.h"
#include "D3D11BaseRenderState.h"
#include "common.h"
namespace Chronos{

    void D3D11Renderer::init(){
        WinChronosWindow * wc = dynamic_cast<WinChronosWindow*>(Chronos::INSTANCE->getWindow());
        if(wc == nullptr){
            Panic(L"fatal");
        }
        device = wc->shareDeivce();
        deviceContext = wc->shareDeviceContext();
        currentContext = nullptr;
        currentRTV = nullptr;
        ZeroMemory(&viewport,sizeof(viewport));
    }

    void D3D11Renderer::createDefaultDevice(ID3D11Device** device,ID3D11DeviceContext** deviceContext){
    }

    void D3D11Renderer::createDefaultRenderTarget(ID3D11RenderTargetView** rtv){

    }
    void D3D11Renderer::setRenderContext(RenderContext * rct){
        currentContext = rct;
        RenderTarget * rt = currentContext->getRenderTarget();
        ChronosD3D11RenderTarget * crt = dynamic_cast<ChronosD3D11RenderTarget*>(rt);
        currentRTV = crt->getRTV();
        viewport =  genViewport(*rct->getCamera());
    }

    D3D11_VIEWPORT D3D11Renderer::genViewport(const Camera& camera){

        D3D11_VIEWPORT dv;
        dv.TopLeftX = 0.f;
        dv.TopLeftY = 0.f;
        dv.Width = camera.getWidth();
        dv.Height = camera.getHeight();
        dv.MinDepth = D3D11_MIN_DEPTH;
        dv.MaxDepth = D3D11_MAX_DEPTH;
        return dv;
    }

    void D3D11Renderer::beginRender() {
        deviceContext->RSSetViewports(1, &viewport);
        deviceContext->OMSetRenderTargets(1, &currentRTV, NULL);
        float color[] = {1.0f,0.1f,0.3f,1.f};
        deviceContext->ClearRenderTargetView(currentRTV, color);
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
       deviceContext->Draw(robj->getVerticesCount(),0);

    }

    void D3D11Renderer::endRender() {
        deviceContext->ClearState();
    }

    std::unique_ptr<RenderTarget> D3D11Renderer::createRenderTarget(){

        WinChronosWindow * wc = dynamic_cast<WinChronosWindow*>(Chronos::INSTANCE->getWindow());
        ComPtr<ID3D11RenderTargetView> rtv;
        unsigned int w,h;
        wc->getSize(w, h);//todo
        ComPtr<ID3D11Texture2D> pBackBuffer;
        CD3D11_TEXTURE2D_DESC tdesc(DXGI_FORMAT_R8G8B8A8_UNORM,w,h);
        tdesc.BindFlags =D3D11_BIND_RENDER_TARGET |D3D11_BIND_SHADER_RESOURCE;
        tdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
        D3D11_SUBRESOURCE_DATA sub;
        ZeroMemory(&sub,sizeof(sub));
        ThrowIfFailed(device->CreateTexture2D(&tdesc,NULL,&pBackBuffer));
        ThrowIfFailed(device->CreateRenderTargetView(pBackBuffer.Get(), NULL,rtv.GetAddressOf()));
        std::unique_ptr<ChronosD3D11RenderTarget> result = std::make_unique<ChronosD3D11RenderTarget>();
        result->setRTV(rtv);
        ComPtr<ID3D11ShaderResourceView> srv;
        D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
        ZeroMemory(&srvd,sizeof(srvd));

        srvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvd.ViewDimension= D3D11_SRV_DIMENSION_TEXTURE2D;
        srvd.Texture2D.MipLevels = 1;

        ThrowIfFailed(device->CreateShaderResourceView(pBackBuffer.Get(), &srvd,srv.GetAddressOf()));
        std::unique_ptr<ChronosD3D11Texture2D> texture = std::make_unique<ChronosD3D11Texture2D>();
        texture->setSRV(srv);
        result->setTexture(std::move(texture));
        return result;
    }

    std::shared_ptr<Shader> D3D11Renderer::loadShader(const std::string& path,ShaderType shaderType){
        throw std::exception("todo");
    }
    std::shared_ptr<Texture> D3D11Renderer::loaderTexture(const std::string& path,TextureParameter tparam){
        throw std::exception("todo");
    }
    D3D11Renderer::~D3D11Renderer(){
    }
}