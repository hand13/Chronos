#pragma once
#include "window/ChronosWindow.h"
#include "engine/ChronosEngine.h"
#include "render/Renderer.h"
namespace Chronos{
    class ChronosGameStarter{
        private:
        ChronosEngine * engine;
        Renderer * renderer;
        ChronosWindow * window;
        public:
        ChronosGameStarter();
        void init(ChronosEngine * engine,Renderer* renderer,ChronosWindow * window);
        void run();
        void begin();
        void show();
    };
}