#include "ChronosGameStarter.h"

#include "base/Utils.h"
#include "engine/EngineState.h"

namespace Chronos {
ChronosGameStarter::ChronosGameStarter() {
    engine = nullptr;
    renderer = nullptr;
    window = nullptr;
}

void ChronosGameStarter::show() { window->show(); }
void ChronosGameStarter::begin() { engine->begin(); }

void ChronosGameStarter::init(ChronosEngine* e, Renderer* r, ChronosWindow* w) {
    engine = e;
    renderer = r;
    window = w;

    renderer->init();
    window->init(renderer);
    SizeU tmpSize;
    window->getSize(tmpSize.width, tmpSize.height);
    engine->initSize(tmpSize);
    engine->init(renderer);
}

void ChronosGameStarter::run() {
    while (engine->getState() != STOP) {
        auto es = window->processEvent();
        engine->pushEvents(es);

        if (engine->getState() != STOP) {
            SizeU tmpSize;
            window->getSize(tmpSize.width, tmpSize.height);
            SizeU eSize = engine->getSize();
            if (tmpSize.width != eSize.width ||
                tmpSize.height != eSize.height) {
                engine->changeSize(tmpSize);
            }
            engine->runInLoop();
            window->displayOffscreen(
                engine->getCurrentScene()->getRenderTargetTextureHandler());
            window->persent();
        }
    }
}
}  // namespace Chronos