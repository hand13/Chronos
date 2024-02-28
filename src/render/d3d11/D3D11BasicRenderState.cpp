#include "D3D11BaseRenderState.h"
#include <cstddef>
#include <d3d11.h>
#include <dxgiformat.h>
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

        std::vector<D3D11_INPUT_ELEMENT_DESC> ied = genInputElementDescFromAttrSet(robj->getAttributeSet());

        vs =std::dynamic_pointer_cast<ChronosVertexShader>((rl->loadShader(vsc->getShaderName()
        , vsc->getShaderType(), true,ied.data(),sizeof(D3D11_INPUT_ELEMENT_DESC)*ied.size())));
        createTmpBuffer();
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

/**
 * @brief tmp code
 * 
 */
        Matrix4fParam * mp = dynamic_cast<Matrix4fParam*>(robj->getVertexProc()->getShaderConfig()->getParamList().getParam("model_matrix"));
        Matrix4f tmp = mp->value;
        dc->UpdateSubresource(tmpConsBuffer.Get(), 0, 0, &tmp,sizeof(tmp),0);
        dc->VSSetConstantBuffers(1,1,tmpConsBuffer.GetAddressOf());//todo


        dc->PSSetShader(ps->getShader(),NULL ,0);//tmp
        applyShaderParam();
        
    }
    void D3D11BaseRenderState::applyShaderParam(){
        //todo
    }

    std::vector<D3D11_INPUT_ELEMENT_DESC> D3D11BaseRenderState::genInputElementDescFromAttrSet(Geometry::AttributeSet* as){
        std::vector<D3D11_INPUT_ELEMENT_DESC> result;
        for(const Geometry::Attribute& attr:as->getAttributes()){
            const char* semantic = nullptr;
            DXGI_FORMAT format = DXGI_FORMAT_R32G32B32_FLOAT;
            if(attr.name == "pos"){
                semantic = "POSITION";
                format = DXGI_FORMAT_R32G32B32_FLOAT;
            }else if(attr.name == "uv"){
                semantic = "TEXCOORD";
                format = DXGI_FORMAT_R32G32_FLOAT;
            }
            UINT offset = as->getAttributeOffset(attr.name);
            D3D11_INPUT_ELEMENT_DESC desc = 
            {semantic,0,format,0,offset,D3D11_INPUT_PER_VERTEX_DATA,0};
            result.push_back(desc);
        }

        // D3D11_INPUT_ELEMENT_DESC BaseVertexLayoutDesc[] =
        // {
        //     { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //     {"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,3*sizeof(float),D3D11_INPUT_PER_VERTEX_DATA,0}
        // };

        return result;
    }
    void D3D11BaseRenderState::createTmpBuffer(){//tmp for test
        ID3D11Device * device = render->getDevice();
        D3D11_BUFFER_DESC bdesc;
        ZeroMemory(&bdesc,sizeof(bdesc));
        bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdesc.Usage = D3D11_USAGE_DEFAULT;
        bdesc.ByteWidth = sizeof(float)*16;
        ThrowIfFailed(device->CreateBuffer(&bdesc, nullptr,tmpConsBuffer.GetAddressOf()));
    }
}