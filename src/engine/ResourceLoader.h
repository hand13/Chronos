#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "IResLoader.h"
#include "model/PolygonModelLoader.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/Texture2D.h"
#include "render/Types.h"

namespace Chronos {
typedef std::map<std::string, std::shared_ptr<Shader>> ShaderMap;
typedef std::map<std::string, std::vector<unsigned char>> FileBufferMap;
typedef std::map<std::string, std::shared_ptr<Texture2D>> TextureMap;
class ResourceLoader : public IResLoader {
   private:
    ShaderMap sm;
    TextureMap tm;
    FileBufferMap fbm;
    PolygonModelLoader pml;

   public:
    virtual std::shared_ptr<Shader> loadShader(const std::string& path,
                                               ShaderType shaderType,
                                               bool cached,
                                               void* exdata = nullptr,
                                               size_t exdataSize = 0) override;
    virtual std::vector<unsigned char> loadFile(const std::string& path,
                                                bool cached) override;
    std::shared_ptr<PolygonModel> loadPolygonModelFromFile(
        const std::string& filePath);
    virtual std::shared_ptr<Texture2D> loadTexture2D(
        const std::string& path, const TextureParameter& tp,
        bool cached = true) override;
    virtual ~ResourceLoader();
};
}  // namespace Chronos