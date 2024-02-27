#include "BaseChronos.h"
#include "BaseScene.h"
#include <memory>
#include "BaseGameObject.h"
class TestScene:public Chronos::BaseScene{
    public:
        virtual void initScene()override{
            spawnObject<Chronos::BaseGameObject>("test");
        }
        virtual ~TestScene(){}
};

class TestChronos:public Chronos::BaseChronos{
    protected:
    virtual void initStartScene()override{
        mainScene = std::make_unique<TestScene>();
        mainScene->init();
    }
};

int main() {

    TestChronos tc;
    Chronos::Chronos::MakeChronosGlobal(&tc);
    tc.init();
    tc.begin();
    tc.loop();
    return 0;
}