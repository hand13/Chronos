#pragma once
#include <d3d11.h>
#include <platform/windows/windows_common.h>
#include <render/VertexShader.h>
#include <wrl/client.h>

namespace Chronos {
class ChronosVertexShader : public VertexShader {
   private:
    ComPtr<ID3D11VertexShader> vs;
    ComPtr<ID3D11InputLayout> il;

   public:
    ChronosVertexShader(ComPtr<ID3D11VertexShader> vs,
                        ComPtr<ID3D11InputLayout> il)
        : vs(vs), il(il) {}
    ID3D11VertexShader* getShader() { return vs.Get(); }
    ID3D11InputLayout* getInputLayout() { return il.Get(); }
    virtual ~ChronosVertexShader() {}
};
}  // namespace Chronos