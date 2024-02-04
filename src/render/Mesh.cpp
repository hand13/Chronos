#include "Mesh.h"
#include <cstddef>
namespace Chronos {
    Mesh::Mesh(){
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
    const std::vector<float>& Mesh::getVertices()const{
        return vertices;
    }
    
    const std::vector<int>& Mesh::getIndices()const{
        return indices;
    }

    Material* Mesh::getMaterial(){
        return material;
    }

    void Mesh::initRenderState(std::unique_ptr<RenderState>&& renderState){
        this->renderState = std::move(renderState);
    }

    RenderState* Mesh::getRenderState(){
        return renderState.get();
    }

    void Mesh::setDirty(bool dirty){
        renderState->setDirty(dirty);
    }
    size_t Mesh::getVerticesCount()const{
        return (vertices.size()*sizeof(float))/as.totalSize();
    }

}