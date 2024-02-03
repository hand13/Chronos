#pragma once
#include "RenderContext.h"
#include "Mesh.h"
#include <memory>

namespace Chronos {
    class Renderer{
        public:
        virtual void setRenderContext(RenderContext * rct) = 0;
        virtual void renderMesh(Mesh * mesh) = 0;

        virtual std::unique_ptr<RenderTarget> createRenderTarget() = 0;
        virtual ~Renderer(){};
    };
}
