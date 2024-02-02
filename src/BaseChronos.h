#pragma once
#include "Chronos.h"
#include "Scene.h"
#include <memory>
#include "render/RenderContext.h"
#include "render/Renderer.h"
#include "ChronosWindow.h"
#include "Option.h"
namespace Chronos {
    class BaseChronos:public Chronos{
        private:
        std::unique_ptr<Scene> mainScene;
        std::unique_ptr<ChronosWindow> window;

        std::unique_ptr<RenderTarget> rt;
        std::unique_ptr<RenderContext> renderContext;
        std::unique_ptr<Renderer> renderer;
        unsigned int state = 0;
        Option option;

        public:
        BaseChronos();
        virtual void init()override;
        virtual void initStartScene() = 0;
        virtual void begin()override;
        virtual void shutdown() override;

        virtual Renderer* getRender()override = 0;
        virtual RenderContext* getRenderContext()override = 0;
        virtual RenderTarget* getRenderTarget()override = 0;
        virtual ChronosWindow* getWindow()override;

        protected:
        void createWindow();
        void createRenderState();
        void createD3D11RenderState();
        virtual void loop()override;
        virtual void render()override;
        virtual void update()override;
        virtual ~BaseChronos();
    };
}