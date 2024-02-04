#pragma once
#include "Scene.h"
#include <memory>
#include "render/RenderContext.h"
#include "render/Mesh.h"

namespace Chronos {
    class BaseScene:public Scene{
        protected:
        std::unique_ptr<RenderTarget> rt;
        Mesh mesh;
        RenderContext rc;
        Camera camera;
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