#pragma once
#include "VertexProc.h"
#include <memory>
#include "BaseShaderConfig.h"
namespace Chronos {
    class DefaultVertexProc:public VertexProc{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        DefaultVertexProc(){
            sc = std::make_unique<BaseShaderConfig>("default_vert",VERTEX_SHADER);
            sc->getParamList().registerParam("model_matrix",ParamType::MATRIX4F);
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~DefaultVertexProc(){};
    };
}