#pragma once
#include <d3d11.h>
#include <platform/windows/windows_common.h>
#include <render/Texture2D.h>
#include <wrl/client.h>

namespace Chronos {
class ChronosD3D11Texture2D : public Texture2D {
   private:
    ComPtr<ID3D11ShaderResourceView> _srv;

   public:
    void setSRV(ComPtr<ID3D11ShaderResourceView> _srv);
    ID3D11ShaderResourceView* getSRV();
    virtual ~ChronosD3D11Texture2D();
};
}  // namespace Chronos