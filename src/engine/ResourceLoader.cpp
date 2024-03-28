#include "ResourceLoader.h"

#include <memory>
#include <vector>

#include "ChronosEngine.h"
#include "base/Log.h"
#include "base/Utils.h"
#include "render/Texture.h"

namespace Chronos {

std::shared_ptr<Shader> ResourceLoader::loadShader(const std::string& path,
                                                   ShaderType shaderType,
                                                   bool cached, void* exdata,
                                                   size_t exdataSize) {
    auto iter = sm.find(path);
    if (iter != sm.end()) {
        return iter->second;
    }
    Renderer* render = Engine->getRenderer();
    std::shared_ptr<Shader> result =
        render->loadShader(path, shaderType, exdata, exdataSize);
    if (cached) {
        sm[path] = result;
    }
    return result;
}

std::shared_ptr<Texture2D> ResourceLoader::loadTexture2D(
    const std::string& path, const TextureParameter& tp, bool cached) {
    auto iter = tm.find(path);
    if (iter != tm.end()) {
        return iter->second;
    }
    Renderer* render = Engine->getRenderer();
    auto result = render->loaderTexture2D(path, tp);
    if (cached) {
        tm[path] = result;
    }
    return result;
}

std::vector<unsigned char> ResourceLoader::loadFile(const std::string& path,
                                                    bool cached) {
    auto iter = fbm.find(path);
    if (iter != fbm.end()) {
        return iter->second;
    }
    std::vector<unsigned char> result = readDataFromFile(path.c_str());
    if (cached) {
        fbm[path] = result;
    }
    return result;
}

std::shared_ptr<PolygonModel> ResourceLoader::loadPolygonModelFromFile(
    const std::string& filePath) {
    return pml.loadPolygonModel(filePath);
}
ResourceLoader::~ResourceLoader() { Log("ResourceLoader destroyed"); }
}  // namespace Chronos