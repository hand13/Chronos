#pragma once
#include "Material.h"
#include <memory>
#include "BaseShaderConfig.h"
#include "base/Param.h"
#include <engine/ChronosEngine.h>

namespace Chronos {
    class PBRMaterial:public Material{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        PBRMaterial(){
            sc = std::make_unique<BaseShaderConfig>("pbr_pixel",PIXEL_SHADER);

            sc->getParamList()
            .registerParam("albedo", ParamType::FLOAT3,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("albedo",Float3(0.f,0.f,0.f));
            sc->getParamList()
            .registerParam("metallic", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("metallic", 0.f);
            sc->getParamList()
            .registerParam("roughness", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("roughness", 0.0f);
            sc->getParamList()
            .registerParam("ao", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("ao", 0.1f);

            sc->getParamList()
            .registerParam("lightPosition", ParamType::FLOAT3,MakePackInfo(1, 0));
            sc->getParamList().setParamValue("lightPosition", Float3(0.f,2.f,0.3f));
            sc->getParamList()
            .registerParam("lightColor", ParamType::FLOAT3,MakePackInfo(1, 0));
            sc->getParamList().setParamValue("lightColor", Float3(20.f,20.f,20.f));

            sc->getParamList()
            .registerParam("camPos", ParamType::FLOAT3,MakePackInfo(2, 0));

            sc->getParamList().registerParam("albedoTex", ParamType::SPTEXTURE2D);
            sc->getParamList().setParamValue("albedoTex", 
                Engine->getResourceLoader()->loadTexture2D("resources/textures/test_albedo.png", TextureParameter{}));
            sc->getParamList().registerParam("metallicTex", ParamType::SPTEXTURE2D);
            sc->getParamList().setParamValue("metallicTex", 
                Engine->getResourceLoader()->loadTexture2D("resources/textures/test_metallic.png", TextureParameter{}));
            sc->getParamList().registerParam("roughnessTex", ParamType::SPTEXTURE2D);
            sc->getParamList().setParamValue("roughnessTex", 
                Engine->getResourceLoader()->loadTexture2D("resources/textures/test_roughness.png", TextureParameter{}));

        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~PBRMaterial(){};
    };
}
