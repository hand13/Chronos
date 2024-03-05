#pragma once
#include "RenderContext.h"
#include "RenderableObject.h"
#include "BaseRenderableObject.h"
#include <memory>
#include <string>
#include "Shader.h"
#include "Types.h"
#include <Utils.h>

namespace Chronos {
    class Renderer{
        public:
        virtual void setRenderContext(RenderContext * rct) = 0;
        virtual void beginRender()=0;
        virtual void endRender() = 0;
        virtual void renderObject(RenderableObject* robj) = 0;
        virtual void renderBaseRenderableObject(BaseRenderableObject * robj) = 0;
        virtual void init() = 0;

        virtual std::shared_ptr<Shader> loadShader(const std::string& path,ShaderType shaderType,void * exdata,size_t exdataSize) = 0;
        virtual std::shared_ptr<Texture2D> loaderTexture2D(const std::string& path,const TextureParameter& tparam) =0;

        virtual std::unique_ptr<RenderTarget> createRenderTarget(const SizeU& size) = 0;

        virtual ~Renderer(){};
    };
}
