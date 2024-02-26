#pragma once
#include "VertexProc.h"
#include <memory>
#include "BaseShaderConfig.h"
namespace Chronos {
    class TestVertexProc:public VertexProc{
        private:
        std::unique_ptr<ShaderConfig> sc;
        public:
        TestVertexProc(){
            sc = std::make_unique<BaseShaderConfig>("test_vert",VERTEX_SHADER);
        }
        virtual ShaderConfig * getShaderConfig(){
            return sc.get();
        }
        virtual ~TestVertexProc(){};
    };
}