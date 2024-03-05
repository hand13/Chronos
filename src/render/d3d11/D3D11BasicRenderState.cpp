#include "D3D11BaseRenderState.h"
#include <cstddef>
#include <d3d11.h>
#include <d3dcommon.h>
#include <dxgiformat.h>
#include <memory>
#include <minwindef.h>
#include <vector>
#include <wrl/client.h>
#include "common.h"
#include <Chronos.h>
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



        ShaderConfig* psc = robj->getMaterial()->getShaderConfig();
        ShaderConfig* vsc = robj->getVertexProc()->getShaderConfig();

        ps = std::dynamic_pointer_cast<ChronosPixelShader>(rl->loadShader(psc->getShaderName(), psc->getShaderType(), true));

        std::vector<D3D11_INPUT_ELEMENT_DESC> ied = genInputElementDescFromAttrSet(robj->getAttributeSet());

        vs =std::dynamic_pointer_cast<ChronosVertexShader>((rl->loadShader(vsc->getShaderName()
        , vsc->getShaderType(), true,ied.data(),sizeof(D3D11_INPUT_ELEMENT_DESC)*ied.size())));

        createBufferForShaderParams();

        dirty = false;
    }

    void D3D11BaseRenderState::apply(){

        transferParamsToConstantBuffers();

        UINT stride = static_cast<UINT>(this->robj->getAttributeSet()->totalSize());
        UINT offset = 0;
        ID3D11DeviceContext* dc = render->getDeviceContext();
        dc->IASetInputLayout(vs->getInputLayout());

        dc->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(robj->drawTopologyType));

        dc->IASetVertexBuffers(0, 1, verticeBuffer.GetAddressOf(), &stride, &offset);
        dc->VSSetShader(vs->getShader(), NULL, 0);
// /**
//  * @brief tmp code
//  * 
//  */
//         Matrix4fParam * mp = dynamic_cast<Matrix4fParam*>(robj->getVertexProc()->getShaderConfig()->getParamList().getParam("model_matrix"));
//         Matrix4f tmp = mp->value;
//         dc->UpdateSubresource(tmpConsBuffer.Get(), 0, 0, &tmp,sizeof(tmp),0);
//         dc->VSSetConstantBuffers(1,1,tmpConsBuffer.GetAddressOf());//todo


        dc->PSSetShader(ps->getShader(),NULL ,0);//tmp
        applyShaderParamConstantBuffers();
        if(indicesBuffer){
            dc->IASetIndexBuffer(indicesBuffer.Get(), DXGI_FORMAT_R32_UINT,0);
            dc->DrawIndexed(static_cast<UINT>(robj->getIndices().size()), 0,0);
        }else{
            dc->Draw(static_cast<UINT>(robj->getVerticesCount()),0);
        }
        // applyShaderParam();
        
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
            }else if(attr.name == "normal"){
                semantic = "NORMAL";
                format = DXGI_FORMAT_R32G32B32_FLOAT;
            }
            UINT offset = static_cast<UINT>(as->getAttributeOffset(attr.name));
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
    ComPtr<ID3D11Buffer> D3D11BaseRenderState::createConstantBuffer(size_t size){
        ComPtr<ID3D11Buffer> result;
        ID3D11Device * device = render->getDevice();
        D3D11_BUFFER_DESC bdesc;
        ZeroMemory(&bdesc,sizeof(bdesc));
        bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bdesc.Usage = D3D11_USAGE_DEFAULT;
        bdesc.ByteWidth = static_cast<UINT>(size);
        ThrowIfFailed(device->CreateBuffer(&bdesc, nullptr,result.GetAddressOf()));
        return result;
    }
    
    void D3D11BaseRenderState::createBufferForShaderParams(){

        ParamList & vpl = robj->getVertexProc()->getShaderConfig()->getParamList();
        for(auto param:vpl.getParamList()){
            size_t size = param->signature().size;
            vertParamConstantBuffers.push_back(createConstantBuffer(size));
        }

        ParamList & ppl = robj->getMaterial()->getShaderConfig()->getParamList();
        for(auto param:ppl.getParamList()){
            size_t size = param->signature().size;
            pixelParamConstantBuffers.push_back(createConstantBuffer(size));
        }
    }

    void D3D11BaseRenderState::transferParamsToConstantBuffers(){
        ID3D11DeviceContext * dc = render->getDeviceContext();

        ParamList & vpl = robj->getVertexProc()->getShaderConfig()->getParamList();
        if(vpl.getParamList().size() != vertParamConstantBuffers.size()){
            Panic("should not happended");
        }

        ParamList & ppl = robj->getMaterial()->getShaderConfig()->getParamList();
        if(ppl.getParamList().size() != pixelParamConstantBuffers.size()){
            Panic("should not happended");
        }

        int vindex = 0;
        for(auto param:vpl.getParamList()){
            dc->UpdateSubresource(vertParamConstantBuffers[vindex].Get(), 0, 0
            , param->asData(),static_cast<UINT>(param->signature().size),0);
            vindex++;
        }

        int pindex= 0;
        for(auto param:ppl.getParamList()){
            dc->UpdateSubresource(pixelParamConstantBuffers[pindex].Get(), 0, 0
            , param->asData(),static_cast<UINT>(param->signature().size),0);
            pindex++;
        }

    }

    void D3D11BaseRenderState::applyShaderParamConstantBuffers(){
        ID3D11DeviceContext* dc = render->getDeviceContext();
        int vslot = 1;//todo
        for(auto cb:vertParamConstantBuffers){
            dc->VSSetConstantBuffers(vslot,1,cb.GetAddressOf());//todo
            vslot++;
        }
        int pslot = 0;//todo
        for(auto cb:pixelParamConstantBuffers){
            dc->PSSetConstantBuffers(pslot,1,cb.GetAddressOf());//todo
            pslot++;
        }
    }
}