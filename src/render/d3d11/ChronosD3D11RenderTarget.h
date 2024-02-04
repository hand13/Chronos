#pragma once
#include "../RenderTarget.h"
#include "common.h"
#include <d3d11.h>
#include <memory>
#include <wrl/client.h>
#include "ChronosD3D11Texture2D.h"
namespace Chronos{
    class ChronosD3D11RenderTarget:public RenderTarget {
        private:
        ComPtr<ID3D11RenderTargetView> _rtv;
        std::unique_ptr<ChronosD3D11Texture2D> texture;
        public:
        void setRTV(ComPtr<ID3D11RenderTargetView> rtv);
        void setTexture(std::unique_ptr<ChronosD3D11Texture2D>&& texture);
        ID3D11RenderTargetView* getRTV();
        virtual Texture2D* asTexture()override;
        virtual ~ChronosD3D11RenderTarget();
    };
}