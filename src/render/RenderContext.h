#pragma once
#include <Camera.h>
#include "RenderTarget.h"
namespace Chronos{
    class RenderContext {
        private:
        Camera* camera;
        RenderTarget* rtv;
        bool useFXAA;
        public:
        RenderContext();
        void setCamera(Camera* camera);
        void setRenderTarget(RenderTarget* rtv);
        void setFXAA(bool useFXAA);
        bool shouldUseFXAA();
        Camera* getCamera();
        RenderTarget* getRenderTarget();
        virtual ~RenderContext(){}
    };
}