#pragma once
#include "engine/ChronosEngine.h"
#include "render/Renderer.h"
#include "window/ChronosWindow.h"

namespace Chronos {
class ChronosGameStarter {
   private:
    ChronosEngine* engine;
    Renderer* renderer;
    ChronosWindow* window;

   public:
    ChronosGameStarter();
    void init(ChronosEngine* engine, Renderer* renderer, ChronosWindow* window);
    void run();
    void begin();
    void show();
};
}  // namespace Chronos