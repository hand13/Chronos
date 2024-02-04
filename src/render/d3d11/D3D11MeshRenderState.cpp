#include "D3D11MeshRenderState.h"
#include <cstddef>
#include <d3d11.h>
#include <minwindef.h>
#include <vector>
#include "common.h"
#include "../../Utils.h"
namespace Chronos{
    D3D11MeshRenderState::D3D11MeshRenderState(D3D11Renderer * render,Mesh * mesh){
        dirty = true;
        this->render = render;
        this->mesh = mesh;
    }

    void D3D11MeshRenderState::setDirty(bool dirty){
        this->dirty= dirty;
    }
    bool D3D11MeshRenderState::isDirty(){
        return dirty;
    }
    void D3D11MeshRenderState::update(){
        ID3D11Device * device = render->getDevice();

        std::vector<float> vertices = mesh->getVertices();
        D3D11_BUFFER_DESC desc;
        ZeroMemory(&desc,sizeof(desc));
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ;
        desc.ByteWidth = vertices.size()*sizeof(float);
        desc.Usage = D3D11_USAGE_DEFAULT;
        D3D11_SUBRESOURCE_DATA sd;
        ZeroMemory(&sd,sizeof(sd));
        sd.pSysMem = vertices.data();
        ThrowIfFailed(render->getDevice()->CreateBuffer(&desc, &sd, verticeBuffer.GetAddressOf()));

        std::vector<unsigned char> vbuffer =readDataFromFile("resources/shader/d3d11/test_vert.cso");
        ThrowIfFailed(device->CreateVertexShader(vbuffer.data()
            , vbuffer.size(),NULL,vertexShader.GetAddressOf()));

        std::vector<unsigned char> pbuffer =readDataFromFile("resources/shader/d3d11/test_pixel.cso");
        ThrowIfFailed(device->CreatePixelShader(pbuffer.data()
            , pbuffer.size(),NULL,pixelShader.GetAddressOf()));

        const D3D11_INPUT_ELEMENT_DESC basicVertexLayoutDesc[] =

            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,3*sizeof(float),D3D11_INPUT_PER_VERTEX_DATA,0}
            };

        ThrowIfFailed(
            device->CreateInputLayout(
                basicVertexLayoutDesc,
                ARRAYSIZE(basicVertexLayoutDesc),
                vbuffer.data(),
                vbuffer.size(),
                inputLayout.GetAddressOf())
            );

            dirty = false;
    }

    void D3D11MeshRenderState::apply(){

        UINT stride = this->mesh->getAttributeSet()->totalSize();
        UINT offset = 0;
        ID3D11DeviceContext* dc = render->getDeviceContext();
        dc->IASetInputLayout(inputLayout.Get());
        dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        dc->IASetVertexBuffers(0, 1, verticeBuffer.GetAddressOf(), &stride, &offset);
        dc->VSSetShader(vertexShader.Get(), NULL, 0);
        dc->PSSetShader(pixelShader.Get(),NULL ,0);//tmp
        
    }
}