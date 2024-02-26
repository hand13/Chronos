#pragma once
#include "RenderableObject.h"
#include "Material.h"
#include "VertexProc.h"
#include <cstddef>
#include <memory>
#include <vector>
#include "AttributeSet.h"
#include "RenderState.h"
namespace Chronos {
    class BaseRenderableObject:public RenderableObject{
        private:
        std::vector<float> vertices;
        std::vector<int> indices;
        std::unique_ptr<Material> material;
        std::unique_ptr<VertexProc> vertexProc;
        Geometry::AttributeSet as;
        std::unique_ptr<RenderState> renderState;//render 所需状态
        public:
        BaseRenderableObject();

        virtual void setDirty(bool dirty)override;
        virtual void initRenderState(std::unique_ptr<RenderState>&& renderState)override;
        virtual RenderState* getRenderState()override;

        void setVertices(const std::vector<float>& vertices);
        void setIndices(const std::vector<int>& indices);

        void setMaterial(std::unique_ptr<Material>&& material);
        void setVertexProc(std::unique_ptr<VertexProc>&& vertexProc);

        void setAttributeSet(const Geometry::AttributeSet& as);

        size_t getVerticesCount()const;
        Geometry::AttributeSet* getAttributeSet(){
            return &as;
        }

        const std::vector<float>& getVertices()const;
        const std::vector<int>& getIndices()const;
        Material* getMaterial();
        VertexProc * getVertexProc();
        virtual ~BaseRenderableObject(){}
    };
}