#pragma once
#include <render/RenderContext.h>
#include <d3d11.h>
#include <wrl/client.h>
#include "common.h"
namespace Chronos {
    class FXAAMan{
        private:
        ComPtr<ID3D11Device> device;
        ComPtr<ID3D11DeviceContext> deviceContext;
        ComPtr<ID3D11VertexShader> vs;
        ComPtr<ID3D11PixelShader> ps;
        ComPtr<ID3D11Buffer> verticeBuffer;
        ComPtr<ID3D11Buffer> constBuffer;
        ComPtr<ID3D11InputLayout> inputLayout;
        ComPtr<ID3D11SamplerState> sampleState;
        void createResource();
        public:
        void apply(RenderContext* rt);
        void init(ComPtr<ID3D11Device> device,ComPtr<ID3D11DeviceContext> deviceContext);
    };
}