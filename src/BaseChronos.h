#pragma once
#include "Chronos.h"
#include "Scene.h"
#include <memory>
#include "render/Renderer.h"
#include "ChronosWindow.h"
#include "Option.h"
namespace Chronos {
    class BaseChronos:public Chronos{
        private:
        std::unique_ptr<Scene> mainScene;
        std::unique_ptr<ChronosWindow> window;

        std::unique_ptr<Renderer> renderer;
        unsigned int state = 0;
        Option option;

        public:
        BaseChronos();
        virtual void init()override;
        virtual void initStartScene() = 0;
        virtual void begin()override;
        virtual void shutdown() override;

        virtual Renderer* getRender()override;
        virtual ChronosWindow* getWindow()override;

        protected:
        void createWindow();
        void createRender();
        void createD3D11Render();
        virtual void loop()override;
        virtual void render()override;
        virtual void update()override;
        virtual ~BaseChronos();
    };
}