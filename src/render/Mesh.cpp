#include "Mesh.h"
namespace Chronos {
    Mesh::Mesh(){
        dirty = true;
    }

    void Mesh::setVertices(const std::vector<float>& vertices){
        this->vertices = vertices;
    }
    void Mesh::setIndices(const std::vector<int>& indices){
        this->indices = indices;
    }
    void Mesh::setMaterial(Material* material){
        this->material = material;
    }
    void Mesh::setAttributeSet(const Geometry::AttributeSet& as){
        this->as =as;
    }
    void Mesh::updateRenderBuffer(std::unique_ptr<RenderBuffer>&& renderBuffer){
        this->renderBuffer = std::move(renderBuffer);
    }

    const std::vector<float>& Mesh::getVertices()const{
        return vertices;
    }
    
    const std::vector<int>& Mesh::getIndices()const{
        return indices;
    }

    bool Mesh::shouldUpdateBuffer()const{
        return dirty == true;
    }

    RenderBuffer* Mesh::getRenderBuffer(){
        return renderBuffer.get();
    }
    Material* Mesh::getMaterial(){
        return material;
    }
}