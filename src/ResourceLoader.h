#pragma once
#include "render/Shader.h"
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "render/Texture.h"
#include "render/Texture2D.h"
#include "render/Types.h"
#include "model/PolygonModelLoader.h"
namespace Chronos {
    typedef std::map<std::string,std::shared_ptr<Shader>> ShaderMap;
    typedef std::map<std::string, std::vector<unsigned char>> FileBufferMap;
    typedef std::map<std::string, std::shared_ptr<Texture2D>> TextureMap;
    class ResourceLoader {
        private:
        ShaderMap sm;
        TextureMap tm;
        FileBufferMap fbm;
        PolygonModelLoader pml;
        public:
        std::shared_ptr<Shader> loadShader(const std::string& path,ShaderType shaderType,bool cached,void * exdata = nullptr,size_t exdataSize = 0);
        std::vector<unsigned char> loadFile(const std::string& path,bool cached);
        std::shared_ptr<PolygonModel> loadPolygonModelFromFile(const std::string& filePath);
        std::shared_ptr<Texture2D> loadTexture2D(const std::string& path,const TextureParameter& tp,bool cached);
    };
}