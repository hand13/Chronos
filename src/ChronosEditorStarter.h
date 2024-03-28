#pragma once
#include "editor/ChronosEditor.h"
#include "engine/ChronosEngine.h"
#include "render/Renderer.h"
namespace Chronos {
class ChronosEditorStarter {
   private:
    ChronosEngine* engine;
    Renderer* renderer;
    ChronosEditor* editor;

   public:
    ChronosEditorStarter();
    void init(ChronosEngine* engine, Renderer* renderer, ChronosEditor* editor);
    void run();
    void begin();
    void show();
};
}  // namespace Chronos