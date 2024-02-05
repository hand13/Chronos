#pragma once
#include "RenderContext.h"
#include "RenderableObject.h"
#include "BaseRenderableObject.h"
#include <memory>
#include <string>
#include "Shader.h"
#include "Types.h"

namespace Chronos {
    class Renderer{
        public:
        virtual void setRenderContext(RenderContext * rct) = 0;
        virtual void beginRender()=0;
        virtual void endRender() = 0;
        virtual void renderObject(RenderableObject* robj) = 0;
        virtual void renderBaseRenderableObject(BaseRenderableObject * robj) = 0;
        virtual void init() = 0;

        virtual std::shared_ptr<Shader> loadShader(const std::string& path,ShaderType shaderType) = 0;
        virtual std::shared_ptr<Texture> loaderTexture(const std::string& path,TextureParameter tparam) =0;

        virtual std::unique_ptr<RenderTarget> createRenderTarget() = 0;

        virtual ~Renderer(){};
    };
}
