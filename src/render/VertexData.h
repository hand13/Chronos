#pragma once
#include <cstddef>
#include <vector>

#include "AttributeSet.h"
#include "BaseRenderStateHolder.h"
#include "DrawTopologyType.h"

namespace Chronos {
class VertexData : public BaseRenderStateHolder {
   private:
    std::vector<float> vertices;
    std::vector<int> indices;
    Geometry::AttributeSet as;

   public:
    VertexData();
    DrawTopologyType drawTopologyType;
    void setVertices(const std::vector<float>& vertices);
    void setIndices(const std::vector<int>& indices);
    void setAttributeSet(const Geometry::AttributeSet& as);

    size_t getVerticesCount() const;
    Geometry::AttributeSet* getAttributeSet() { return &as; }
    const std::vector<float>& getVertices() const;
    const std::vector<int>& getIndices() const;
    bool useIndices() const { return true; };
    virtual ~VertexData() {}
};
}  // namespace Chronos