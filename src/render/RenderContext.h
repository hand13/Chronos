#pragma once
#include "../Camera.h"
#include "RenderTarget.h"
namespace Chronos{
    class RenderContext {
        private:
        Camera* camera;
        RenderTarget* rtv;
        public:
        RenderContext();
        void setCamera(Camera* camera);
        void setRenderTarget(RenderTarget* rtv);
        Camera* getCamera();
        RenderTarget* getRenderTarget();
        virtual ~RenderContext(){}
    };
}