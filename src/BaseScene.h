#pragma once
#include "Scene.h"
#include <memory>

namespace Chronos {
    class BaseScene:public Scene{
        protected:
        std::unique_ptr<RenderTarget> rt;
        virtual RenderTarget* getRenderTarget();
        virtual Texture2D* getRenderTargetAsTexture();

        virtual void init();
        virtual void initRenderState();
        virtual void initScene() = 0;

        virtual void begin();
        virtual void render();
        virtual void update();
        public:
        virtual ~BaseScene();
    };
}