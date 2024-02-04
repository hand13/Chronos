#pragma once
#include "RenderableObject.h"
#include "Material.h"
#include <cstddef>
#include <memory>
#include <vector>
#include "AttributeSet.h"
#include "RenderState.h"
namespace Chronos {
    class Mesh :public RenderableObject{
        private:
        std::vector<float> vertices;
        std::vector<int> indices;
        Material* material;
        Geometry::AttributeSet as;
        std::unique_ptr<RenderState> renderState;//render 所需状态
        public:
        Mesh();

        virtual void setDirty(bool dirty)override;
        virtual void initRenderState(std::unique_ptr<RenderState>&& renderState)override;
        virtual RenderState* getRenderState()override;

        void setVertices(const std::vector<float>& vertices);
        void setIndices(const std::vector<int>& indices);
        void setMaterial(Material* material);
        void setAttributeSet(const Geometry::AttributeSet& as);

        size_t getVerticesCount()const;
        Geometry::AttributeSet* getAttributeSet(){
            return &as;
        }

        const std::vector<float>& getVertices()const;
        const std::vector<int>& getIndices()const;
        Material* getMaterial();
    };
}