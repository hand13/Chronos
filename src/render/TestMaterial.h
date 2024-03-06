#pragma once
#include "Material.h"
#include <memory>
#include "BaseShaderConfig.h"
#include "Param.h"
#include "render/Texture.h"
#include <ChronosEngine.h>
namespace Chronos {
    class TestMaterial:public Material{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        TestMaterial(){
            sc = std::make_unique<BaseShaderConfig>("basic_pixel",PIXEL_SHADER);
            sc->getParamList().registerParam("texture", ParamType::SPTEXTURE2D);
            sc->getParamList().setParamValue("texture", 
                Engine->getResourceLoader()->loadTexture2D("resources/textures/test.png", TextureParameter{}));
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~TestMaterial(){};
    };
}