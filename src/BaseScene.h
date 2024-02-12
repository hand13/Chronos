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

        int lastMouseX;
        int lastMouseY;

        virtual void init()override;
        virtual void initRenderState();
        virtual void initScene() = 0;
        public:
        BaseScene();
        virtual RenderTarget* getRenderTarget()override;
        virtual Texture2D* getRenderTargetAsTexture()override;
        virtual void begin()override;
        virtual void render()override;
        virtual void update()override;
        virtual void processEvent(const IOEvent& event)override;
        virtual void changeSize(const SizeU& windowSize)override;
        public:
        virtual ~BaseScene();
    };
}