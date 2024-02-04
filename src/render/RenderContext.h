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
        const Camera* getCamera()const;
        RenderTarget* getRenderTarget();
        virtual ~RenderContext(){}
    };
}