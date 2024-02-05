#pragma once
#include "Scene.h"
#include <memory>
#include "render/RenderContext.h"
#include "render/BaseRenderableObject.h"

namespace Chronos {
    class BaseScene:public Scene{
        protected:
        std::unique_ptr<RenderTarget> rt;
        BaseRenderableObject robj;
        RenderContext rc;
        Camera camera;

        virtual void init();
        virtual void initRenderState();
        virtual void initScene() = 0;
        public:
        virtual RenderTarget* getRenderTarget();
        virtual Texture2D* getRenderTargetAsTexture();
        virtual void begin();
        virtual void render();
        virtual void update();
        virtual void changeSize(const SizeU& windowSize);
        public:
        virtual ~BaseScene();
    };
}