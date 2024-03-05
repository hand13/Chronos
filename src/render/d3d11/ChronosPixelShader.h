#include <render/PixelShader.h>
#include <d3d11.h>
#include <wrl/client.h>
#include "common.h"
namespace Chronos{
    class ChronosPixelShader:public PixelShader{
        private:
        ComPtr<ID3D11PixelShader> ps;
        public:
        ChronosPixelShader(ComPtr<ID3D11PixelShader> ps):ps(ps){}
        ID3D11PixelShader * getShader(){
            return ps.Get();
        }
        virtual ~ChronosPixelShader(){}
    };
}