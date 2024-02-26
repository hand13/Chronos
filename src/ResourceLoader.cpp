#include "ResourceLoader.h"
#include "Utils.h"
#include <memory>
#include <vector>
#include "Chronos.h"
namespace Chronos {

    std::shared_ptr<Shader> ResourceLoader::loadShader(const std::string& path,ShaderType shaderType,bool cached,void * exdata,size_t exdataSize){
        auto iter = sm.find(path);
        if(iter != sm.end()){
            return iter->second;
        }
        Renderer * render = Chronos::INSTANCE->getRender();
        std::shared_ptr<Shader> result = render->loadShader(path, shaderType,exdata,exdataSize);
        if(cached){
        }
        return result;
    }

    std::vector<unsigned char> ResourceLoader::loadFile(const std::string& path,bool cached){
        auto iter = fbm.find(path);
        if(iter != fbm.end()){
            return iter->second;
        }
        std::vector<unsigned char> result = readDataFromFile(path.c_str());
        if(cached){
            fbm[path] = result;
        }
        return result;
    }
}