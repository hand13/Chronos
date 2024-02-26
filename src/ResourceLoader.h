#pragma once
#include "render/Shader.h"
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "render/Types.h"
namespace Chronos {
    typedef std::map<std::string,std::shared_ptr<Shader>> ShaderMap;
    typedef std::map<std::string, std::vector<unsigned char>> FileBufferMap;
    class ResourceLoader {
        private:
        ShaderMap sm;
        FileBufferMap fbm;
        public:
        std::shared_ptr<Shader> loadShader(const std::string& path,ShaderType shaderType,bool cached,void * exdata = nullptr,size_t exdataSize = 0);
        std::vector<unsigned char> loadFile(const std::string& path,bool cached);
    };
}