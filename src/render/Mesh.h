#pragma once
#include "RenderableObject.h"
#include "Material.h"
#include <memory>
#include <vector>
#include "AttributeSet.h"
#include "RenderBuffer.h"
namespace Chronos {
    class Mesh :public RenderableObject{
        private:
        std::vector<float> vertices;
        std::vector<int> indices;
        bool dirty;
        Material* material;
        Geometry::AttributeSet as;
        std::unique_ptr<RenderBuffer> renderBuffer;
        public:
        Mesh();

        void setVertices(const std::vector<float>& vertices);
        void setIndices(const std::vector<int>& indices);
        void setMaterial(Material* material);
        void setAttributeSet(const Geometry::AttributeSet& as);
        void updateRenderBuffer(std::unique_ptr<RenderBuffer>& renderBuffer);

        const std::vector<float>& getVertices()const;
        const std::vector<int>& getIndices()const;
        bool shouldUpdateBuffer()const;
        RenderBuffer* getRenderBuffer();
        Material* getMaterial();
    };
}