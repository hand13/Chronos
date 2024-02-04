#pragma once
#include "RenderState.h"
#include <memory>
namespace Chronos{
    class RenderableObject {
        public:
        virtual void setDirty(bool dirty) = 0;
        virtual void initRenderState(std::unique_ptr<RenderState>&& renderState) = 0;
        virtual RenderState* getRenderState() = 0;
        virtual ~RenderableObject(){}
    };
}