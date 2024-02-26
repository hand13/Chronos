#pragma once
#include "Material.h"
#include <memory>
#include "BaseShaderConfig.h"
namespace Chronos {
    class TestMaterial:public Material{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        TestMaterial(){
            sc = std::make_unique<BaseShaderConfig>("test_pixel",PIXEL_SHADER);
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~TestMaterial(){};
    };
}