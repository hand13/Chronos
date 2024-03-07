#pragma once
#include "VertexProc.h"
#include <memory>
#include "BaseShaderConfig.h"
namespace Chronos {
    class PBRVertexProc:public VertexProc{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        PBRVertexProc(){
            sc = std::make_unique<BaseShaderConfig>("pbr_vert",VERTEX_SHADER);
            sc->getParamList().registerParam("model_matrix",ParamType::MATRIX4F,MakePackInfo(1,0));
            sc->getParamList().registerParam("normal_matrix",ParamType::MATRIX4F,MakePackInfo(1,0));
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~PBRVertexProc(){};
    };
}