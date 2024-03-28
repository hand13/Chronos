#include "ChronosD3D11RenderTarget.h"

namespace Chronos {

void ChronosD3D11RenderTarget::setRTV(ComPtr<ID3D11RenderTargetView> rtv) {
    _rtv = rtv;
}
ID3D11RenderTargetView* ChronosD3D11RenderTarget::getRTV() {
    return _rtv.Get();
}
ChronosD3D11RenderTarget::~ChronosD3D11RenderTarget() {}
void ChronosD3D11RenderTarget::setTexture(
    std::unique_ptr<ChronosD3D11Texture2D>&& texture) {
    this->texture = std::move(texture);
}

Texture2D* ChronosD3D11RenderTarget::asTexture() { return texture.get(); }

void* ChronosD3D11RenderTarget::asTextureHandler() { return texture->getSRV(); }

void ChronosD3D11RenderTarget::setInnerRTV(
    ComPtr<ID3D11RenderTargetView> innerRTV) {
    _innerRTV = innerRTV;
}
void ChronosD3D11RenderTarget::setInnerTexture(
    std::unique_ptr<ChronosD3D11Texture2D>&& innerTexture) {
    this->_innerTexture = std::move(innerTexture);
}

ID3D11RenderTargetView* ChronosD3D11RenderTarget::getInnerRTV() {
    return _innerRTV.Get();
}
Texture2D* ChronosD3D11RenderTarget::innerAsTexture() {
    return _innerTexture.get();
}

void ChronosD3D11RenderTarget::setDSV(ComPtr<ID3D11DepthStencilView> dsv) {
    _dsv = dsv;
}
ID3D11DepthStencilView* ChronosD3D11RenderTarget::getDSV() {
    return _dsv.Get();
}
}  // namespace Chronos