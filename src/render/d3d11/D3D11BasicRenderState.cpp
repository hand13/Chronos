#include "D3D11BaseRenderState.h"
#include <cstddef>
#include <d3d11.h>
#include <memory>
#include <minwindef.h>
#include <vector>
#include "common.h"
#include "../../Chronos.h"
namespace Chronos{
    D3D11BaseRenderState::D3D11BaseRenderState(D3D11Renderer * render,BaseRenderableObject * robj){
        dirty = true;
        this->render = render;
        this->robj = robj;
    }

    void D3D11BaseRenderState::setDirty(bool dirty){
        this->dirty= dirty;
    }
    bool D3D11BaseRenderState::isDirty(){
        return dirty;
    }
    void D3D11BaseRenderState::update(){

        ResourceLoader * rl = Chronos::INSTANCE->getResourceLoader();

        ID3D11Device * device = render->getDevice();

        std::vector<float> vertices = robj->getVertices();
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

        ShaderConfig* psc = robj->getMaterial()->getShaderConfig();
        ShaderConfig* vsc = robj->getVertexProc()->getShaderConfig();

        ps = std::dynamic_pointer_cast<ChronosPixelShader>(rl->loadShader(psc->getShaderName(), psc->getShaderType(), true));

        D3D11_INPUT_ELEMENT_DESC BaseVertexLayoutDesc[] =

            {
                { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,3*sizeof(float),D3D11_INPUT_PER_VERTEX_DATA,0}
            };

        vs =std::dynamic_pointer_cast<ChronosVertexShader>((rl->loadShader(vsc->getShaderName()
        , vsc->getShaderType(), true,BaseVertexLayoutDesc,sizeof(BaseVertexLayoutDesc))));

        dirty = false;
    }

    void D3D11BaseRenderState::apply(){

        UINT stride = this->robj->getAttributeSet()->totalSize();
        UINT offset = 0;
        ID3D11DeviceContext* dc = render->getDeviceContext();
        dc->IASetInputLayout(vs->getInputLayout());
        dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        dc->IASetVertexBuffers(0, 1, verticeBuffer.GetAddressOf(), &stride, &offset);
        dc->VSSetShader(vs->getShader(), NULL, 0);
        dc->PSSetShader(ps->getShader(),NULL ,0);//tmp
        
    }
}