#include "BaseChronosEngine.h"
#include "BaseScene.h"
#include <memory>
#include "TestGameObject.h"
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
    TestChronosEngine tc;
    Chronos::MakeChronosGlobal(&tc);
    tc.init();
    tc.begin();
    tc.loop();

    return 0;
}