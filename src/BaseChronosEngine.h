#pragma once
#include "ChronosEngine.h"
#include "Scene.h"
#include <memory>
#include "render/Renderer.h"
#include "ChronosWindow.h"
#include "Option.h"
#include "Utils.h"
#include "Timer.h"
#include "imgui_control/TestUI.h"
namespace Chronos {
    class BaseChronosEngine:public ChronosEngine{
        protected:
        Timer timer;
        std::unique_ptr<Scene> mainScene;

        std::unique_ptr<ChronosWindow> window;
        std::unique_ptr<TestUI> cui;//tmp
        std::unique_ptr<Renderer> renderer;

        unsigned int state = 0;
        Option option;
        ResourceLoader resourceLoader;
        SizeU windowSize;
        boolean enableImgui;
        public:
        BaseChronosEngine();
        virtual void init()override;
        virtual void begin()override;
        virtual void loop()override;
        virtual void shutdown() override;
        virtual ResourceLoader* getResourceLoader() override;

        virtual Renderer* getRenderer()override;
        virtual ChronosWindow* getWindow()override;
        virtual void changeSize();
        virtual SizeU getWindowSize()const override;
        protected:
        virtual void initStartScene() = 0;
        void createWindow();
        void createRender();
        void createD3D11Render();
        virtual void render()override;
        virtual void update()override;
        virtual ~BaseChronosEngine();
    };
}