#pragma once
#include "Material.h"
#include <memory>
#include "BaseShaderConfig.h"
#include "Param.h"

namespace Chronos {
    class PBRMaterial:public Material{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        PBRMaterial(){

            sc = std::make_unique<BaseShaderConfig>("pbr_pixel",PIXEL_SHADER);

            sc->getParamList()
            .registerParam("albedo", ParamType::FLOAT3,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("albedo",Float3(1.f,0.f,0.f));
            sc->getParamList()
            .registerParam("metallic", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("metallic", 0.f);
            sc->getParamList()
            .registerParam("roughness", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("roughness", 0.5f);
            sc->getParamList()

            .registerParam("ao", ParamType::FLOAT,MakePackInfo(0, 0));
            sc->getParamList().setParamValue("ao", 0.1f);

            sc->getParamList()
            .registerParam("lightPosition", ParamType::FLOAT3,MakePackInfo(1, 0));
            sc->getParamList().setParamValue("lightPosition", Float3(0.f,1.2f,0.3f));

            sc->getParamList()
            .registerParam("lightColor", ParamType::FLOAT3,MakePackInfo(1, 0));
            sc->getParamList().setParamValue("lightColor", Float3(1.f,1.f,1.f));

            sc->getParamList()
            .registerParam("camPos", ParamType::FLOAT3,MakePackInfo(2, 0));
            // sc->getParamList().setParamValue("camPos", Float3(0.f,4.f,0.f));
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~PBRMaterial(){};
    };
}
