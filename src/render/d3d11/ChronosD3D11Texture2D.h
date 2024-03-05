#pragma once
#include <render/Texture2D.h>
#include "common.h"
#include <d3d11.h>
#include <wrl/client.h>
namespace Chronos{
    class ChronosD3D11Texture2D:public Texture2D{
        private:
        ComPtr<ID3D11ShaderResourceView> _srv;
        public:
        void setSRV(ComPtr<ID3D11ShaderResourceView> _srv);
        ID3D11ShaderResourceView* getSRV();
        virtual ~ChronosD3D11Texture2D();
    };
}