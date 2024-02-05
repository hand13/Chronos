#include "BaseRenderableObject.h"
#include <cstddef>
namespace Chronos {
    BaseRenderableObject::BaseRenderableObject(){
    }

    void BaseRenderableObject::setVertices(const std::vector<float>& vertices){
        this->vertices = vertices;
    }
    void BaseRenderableObject::setIndices(const std::vector<int>& indices){
        this->indices = indices;
    }
    void BaseRenderableObject::setMaterial(Material* material){
        this->material = material;
    }
    void BaseRenderableObject::setAttributeSet(const Geometry::AttributeSet& as){
        this->as =as;
    }
    const std::vector<float>& BaseRenderableObject::getVertices()const{
        return vertices;
    }
    
    const std::vector<int>& BaseRenderableObject::getIndices()const{
        return indices;
    }

    Material* BaseRenderableObject::getMaterial(){
        return material;
    }

    void BaseRenderableObject::initRenderState(std::unique_ptr<RenderState>&& renderState){
        this->renderState = std::move(renderState);
    }

    RenderState* BaseRenderableObject::getRenderState(){
        return renderState.get();
    }

    void BaseRenderableObject::setDirty(bool dirty){
        renderState->setDirty(dirty);
    }
    size_t BaseRenderableObject::getVerticesCount()const{
        return (vertices.size()*sizeof(float))/as.totalSize();
    }

}