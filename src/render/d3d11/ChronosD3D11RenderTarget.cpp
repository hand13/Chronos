#include "ChronosD3D11RenderTarget.h"

namespace Chronos{

    void ChronosD3D11RenderTarget::setRTV(ComPtr<ID3D11RenderTargetView> rtv){
        _rtv = rtv;
    }
    ID3D11RenderTargetView* ChronosD3D11RenderTarget::getRTV(){
        return _rtv.Get();
    }
    ChronosD3D11RenderTarget::~ChronosD3D11RenderTarget(){
    }
    void ChronosD3D11RenderTarget::setTexture(std::unique_ptr<ChronosD3D11Texture2D>&& texture){
        this->texture = std::move(texture);
    }

    Texture2D* ChronosD3D11RenderTarget::asTexture(){
        return texture.get();
    }
}