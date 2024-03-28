#pragma once
#include <base/Utils.h>

#include <memory>
#include <string>

#include "Material.h"
#include "RenderConstantData.h"
#include "RenderContext.h"
#include "Shader.h"
#include "Types.h"
#include "VertexData.h"
#include "VertexProc.h"


namespace Chronos {
class Renderer {
   public:
    virtual void setRenderContext(RenderContext* rct) = 0;
    virtual void beginRender() = 0;
    virtual void endRender() = 0;
    virtual void render(VertexData& vertexData, VertexProc& vertexProc,
                        Material& material, const RenderConstantData& rcd) = 0;
    virtual void init() = 0;

    virtual std::shared_ptr<Shader> loadShader(const std::string& path,
                                               ShaderType shaderType,
                                               void* exdata,
                                               size_t exdataSize) = 0;
    virtual std::shared_ptr<Texture2D> loaderTexture2D(
        const std::string& path, const TextureParameter& tparam) = 0;

    virtual std::unique_ptr<RenderTarget> createRenderTarget(
        const SizeU& size) = 0;

    virtual ~Renderer(){};
};
}  // namespace Chronos
