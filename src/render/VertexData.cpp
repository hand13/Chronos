#include "VertexData.h"
#include <cstddef>
namespace Chronos {
    VertexData::VertexData(){
        drawTopologyType = CHRONOS_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    }

    void VertexData::setVertices(const std::vector<float>& vertices){
        this->vertices = vertices;
    }
    void VertexData::setIndices(const std::vector<int>& indices){
        this->indices = indices;
    }
    void VertexData::setAttributeSet(const Geometry::AttributeSet& as){
        this->as =as;
    }
    const std::vector<float>& VertexData::getVertices()const{
        return vertices;
    }
    
    const std::vector<int>& VertexData::getIndices()const{
        return indices;
    }
    size_t VertexData::getVerticesCount()const{
        return (vertices.size()*sizeof(float))/as.totalSize();
    }

}