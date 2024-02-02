#pragma once
#include "RenderableObject.h"
#include "RenderContext.h"
namespace Chronos {
    class Renderer{
        public:
        virtual void setRenderContext(RenderContext * rct) = 0;
        virtual void render(RenderableObject * robj) = 0;;
        virtual ~Renderer(){};
    };
}