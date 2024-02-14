#pragma once
#include "../RenderTarget.h"
#include "common.h"
#include <d3d11.h>
#include <memory>
#include <rpcndr.h>
#include <wrl/client.h>
#include "ChronosD3D11Texture2D.h"
namespace Chronos{
    class ChronosD3D11RenderTarget:public RenderTarget {
        private:

        ComPtr<ID3D11RenderTargetView> _rtv;
        std::unique_ptr<ChronosD3D11Texture2D> texture;

        ComPtr<ID3D11RenderTargetView> _innerRTV;
        std::unique_ptr<ChronosD3D11Texture2D> _innerTexture;
        public:

        void setRTV(ComPtr<ID3D11RenderTargetView> rtv);
        void setTexture(std::unique_ptr<ChronosD3D11Texture2D>&& texture);

        void setInnerRTV(ComPtr<ID3D11RenderTargetView> innerRtv);
        void setInnerTexture(std::unique_ptr<ChronosD3D11Texture2D>&& innerTexture);

        ID3D11RenderTargetView* getRTV();
        virtual Texture2D* asTexture()override;

        ID3D11RenderTargetView* getInnerRTV();
        Texture2D* innerAsTexture();

        virtual ~ChronosD3D11RenderTarget();
    };
}