#pragma once
#include "render/Shader.h"
#include <memory>
#include <string>
#include <vector>
#include "render/Texture.h"
#include "render/Texture2D.h"
#include "render/Types.h"
namespace Chronos {
    class IResLoader {
        public:
        virtual std::shared_ptr<Shader> loadShader(const std::string& path,ShaderType shaderType,bool cached,void * exdata = nullptr,size_t exdataSize = 0) =0;
        virtual std::vector<unsigned char> loadFile(const std::string& path,bool cached) = 0;
        virtual std::shared_ptr<Texture2D> loadTexture2D(const std::string& path,const TextureParameter& tp,bool cached = true) = 0;
        virtual ~IResLoader(){};
    };
}