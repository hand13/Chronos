#include "engine/BaseChronosEngine.h"
#include "engine/BaseScene.h"
#include <memory>
#include "TestGameObject.h"
#include "module/ModuleLoader.h"
class TestScene:public Chronos::BaseScene{
    public:
        virtual void initScene()override{
            spawnObject<Chronos::TestGameObject>("test")->init();
        }
        virtual ~TestScene(){}
};

class TestChronosEngine:public Chronos::BaseChronosEngine{
    protected:
    virtual void initStartScene()override{
        mainScene = std::make_unique<TestScene>();
        mainScene->init();
    }
};

int main() {
    Chronos::ModuleLoader ml;

    TestChronosEngine tc;
    Chronos::MakeChronosGlobal(&tc);
    tc.setModuleLoader(&ml);
    tc.init();
    tc.begin();
    tc.loop();

    return 0;
}