#pragma once
#include <d3d11.h>
#include <platform/windows/windows_common.h>
#include <render/RenderTarget.h>
#include <rpcndr.h>
#include <wrl/client.h>

#include <memory>

#include "ChronosD3D11Texture2D.h"

namespace Chronos {
class ChronosD3D11RenderTarget : public RenderTarget {
   private:
    ComPtr<ID3D11RenderTargetView> _rtv;
    std::unique_ptr<ChronosD3D11Texture2D> texture;

    ComPtr<ID3D11RenderTargetView> _innerRTV;
    std::unique_ptr<ChronosD3D11Texture2D> _innerTexture;

    ComPtr<ID3D11DepthStencilView> _dsv;

   public:
    void setRTV(ComPtr<ID3D11RenderTargetView> rtv);
    void setTexture(std::unique_ptr<ChronosD3D11Texture2D>&& texture);

    void setInnerRTV(ComPtr<ID3D11RenderTargetView> innerRtv);
    void setInnerTexture(std::unique_ptr<ChronosD3D11Texture2D>&& innerTexture);

    ID3D11RenderTargetView* getRTV();
    virtual Texture2D* asTexture() override;
    virtual void* asTextureHandler() override;

    ID3D11RenderTargetView* getInnerRTV();
    Texture2D* innerAsTexture();

    void setDSV(ComPtr<ID3D11DepthStencilView> dsv);
    ID3D11DepthStencilView* getDSV();

    virtual ~ChronosD3D11RenderTarget();
};
}  // namespace Chronos