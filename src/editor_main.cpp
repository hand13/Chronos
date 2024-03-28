#include <base/Log.h>

#include "ChronosEditorStarter.h"
#include "TestGameObject.h"
#include "editor/ChronosEditor.h"
#include "engine/BaseChronosEngine.h"
#include "engine/BaseScene.h"
#include "module/IRendererModule.h"
#include "module/ModuleLoader.h"
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
    Chronos::LoggerConfig lc;
    lc.initLogger();

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
    Chronos::ChronosEditor editor;

    Chronos::ChronosEditorStarter starter;
    starter.init(&tc, renderer, &editor);
    starter.show();
    starter.begin();
    starter.run();
    return 0;
}