#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <minwindef.h>
#include <wrl/client.h>
#include "D3D11VertexDataRenderState.h"
#include "render/RenderConstantData.h"
#include "render/VertexData.h"

namespace Chronos{
    D3D11VertexDataRenderState::D3D11VertexDataRenderState(D3D11Renderer * render,VertexData * robj){
        this->render = render;
        this->robj = robj;
    }

    void D3D11VertexDataRenderState::update(){
        {
            std::vector<float> vertices = robj->getVertices();
            D3D11_BUFFER_DESC desc;
            ZeroMemory(&desc,sizeof(desc));
            desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
            desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
            desc.ByteWidth = static_cast<UINT>(vertices.size()*sizeof(float));
            desc.Usage = D3D11_USAGE_DEFAULT;
            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd,sizeof(sd));
            sd.pSysMem = vertices.data();
            ThrowIfFailed(render->getDevice()->CreateBuffer(&desc, &sd, verticeBuffer.GetAddressOf()));
        }

        if(robj->getIndices().size() != 0){
            std::vector<int> indices = robj->getIndices();
            D3D11_BUFFER_DESC desc;
            ZeroMemory(&desc,sizeof(desc));
            desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
            desc.ByteWidth = static_cast<UINT>(indices.size()*sizeof(int));
            desc.Usage = D3D11_USAGE_DEFAULT;
            D3D11_SUBRESOURCE_DATA sd;
            ZeroMemory(&sd,sizeof(sd));
            sd.pSysMem = indices.data();
            ThrowIfFailed(render->getDevice()->CreateBuffer(&desc, &sd, indicesBuffer.GetAddressOf()));
        }
        dirty = false;

    }

    void D3D11VertexDataRenderState::applyWith(const RenderConstantData& rcd){

        // transferParamsToConstantBuffers();

        UINT stride = static_cast<UINT>(this->robj->getAttributeSet()->totalSize());
        UINT offset = 0;
        ID3D11DeviceContext* dc = render->getDeviceContext();
        dc->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(robj->drawTopologyType));
        dc->IASetVertexBuffers(0, 1, verticeBuffer.GetAddressOf(), &stride, &offset);
        if(indicesBuffer){
            dc->IASetIndexBuffer(indicesBuffer.Get(), DXGI_FORMAT_R32_UINT,0);
        }
    }

    D3D11VertexDataRenderState::~D3D11VertexDataRenderState(){
    }
}