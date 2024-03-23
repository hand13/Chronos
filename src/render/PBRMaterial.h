#pragma once
#include "Material.h"
#include <memory>
#include "BaseShaderConfig.h"
#include <base/Utils.h>
#include "render/ShaderConfig.h"
#include <engine/ChronosEngine.h>

namespace Chronos {


    class PBRMaterial:public Material{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        struct PBRMaterialAttr{
            Float3 albedo;
            float metallic;
            float roughness;
            float ao;
        };

        struct PBRMaterialLight{
            Float3 lightPosition;
            float _pad;
            Float3 lightColor;
        };

        struct PBRMaterialCamera{
            Float3 cameraPos;
        };
        PBRMaterial(){
            sc = std::make_unique<BaseShaderConfig>("pbr_pixel",PIXEL_SHADER);
            sc->registerConstantDataDef(ConstantDataDef("attr",CDT_ConstantBuffer
            ,sizeof(PBRMaterialAttr),0));
            sc->registerConstantDataDef(ConstantDataDef("light",CDT_ConstantBuffer
            ,sizeof(PBRMaterialLight),1));
            sc->registerConstantDataDef(ConstantDataDef("camera",CDT_ConstantBuffer
            ,sizeof(PBRMaterialCamera),2));
            sc->registerConstantDataDef(ConstantDataDef("albedo_texture",CDT_Texture2D
            ,0,0));
            sc->registerConstantDataDef(ConstantDataDef("metallic_texture",CDT_Texture2D
            ,0,1));
            sc->registerConstantDataDef(ConstantDataDef("roughness_texture",CDT_Texture2D
            ,0,2));

        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~PBRMaterial(){};
    };
}
