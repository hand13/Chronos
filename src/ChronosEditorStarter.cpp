#include "ChronosEditorStarter.h"

#include "base/Utils.h"
#include "editor/ChronosEditor.h"


namespace Chronos {
ChronosEditorStarter::ChronosEditorStarter() {
    engine = nullptr;
    renderer = nullptr;
    editor = nullptr;
}

void ChronosEditorStarter::show() { editor->show(); }
void ChronosEditorStarter::begin() { engine->begin(); }

void ChronosEditorStarter::init(ChronosEngine* e, Renderer* r,
                                ChronosEditor* ed) {
    engine = e;
    renderer = r;
    editor = ed;

    renderer->init();
    editor->init(renderer);
    engine->initSize(SizeU(1280, 720));
    engine->init(renderer);
}

void ChronosEditorStarter::run() {
    while (!editor->isStop()) {
        auto es = editor->getEvents();
        engine->pushEvents(es);

        if (!editor->isStop()) {
            engine->runInLoop();
            editor->setScene(engine->getCurrentScene());
            editor->displayOffscreen(
                engine->getCurrentScene()->getRenderTargetTextureHandler());
            editor->runInLoop();
        }
    }
}
}  // namespace Chronos