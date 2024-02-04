#pragma once
#include "RenderContext.h"
#include "RenderableObject.h"
#include <memory>

namespace Chronos {
    class Renderer{
        public:
        virtual void setRenderContext(RenderContext * rct) = 0;
        virtual void beginRender()=0;
        virtual void endRender() = 0;
        virtual void renderObject(RenderableObject* robj) = 0;
        virtual void init() = 0;

        virtual std::unique_ptr<RenderTarget> createRenderTarget() = 0;
        virtual ~Renderer(){};
    };
}
