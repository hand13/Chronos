#include <memory>

#include "ChronosGameStarter.h"
#include "TestGameObject.h"
#include "engine/BaseChronosEngine.h"
#include "engine/BaseScene.h"
#include "module/IRendererModule.h"
#include "module/ModuleLoader.h"
#include "platform/windows/window/d3d11/WinChronosWindow.h"
#include "render/Renderer.h"

class TestScene : public Chronos::BaseScene {
   public:
    virtual void initScene() override {
        spawnObject<Chronos::TestGameObject>("test")->init();
    }
    virtual ~TestScene() {}
};

class TestChronosEngine : public Chronos::BaseChronosEngine {
   protected:
    virtual void initStartScene() override {
        mainScene = std::make_unique<TestScene>();
        mainScene->init();
    }
};

int main() {
    Chronos::ModuleLoader ml;

    TestChronosEngine tc;
    Chronos::MakeChronosGlobal(&tc);

    Chronos::ICModule* im = ml.installModule("d3d11_renderer.dll");
    Chronos::IRendererModule* rendererModule = nullptr;
    Chronos::Renderer* renderer = nullptr;
    if (im && (rendererModule = dynamic_cast<Chronos::IRendererModule*>(im))) {
        renderer = rendererModule->getRenderer();
    } else {
        Panic("not a renderer");
    }
    Chronos::WinChronosWindow wcw;

    Chronos::ChronosGameStarter gs;
    gs.init(&tc, renderer, &wcw);
    gs.show();
    gs.begin();
    gs.run();
    return 0;
}