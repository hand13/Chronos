#include "TestGameObject.h"
#include <memory>
namespace Chronos{
    void TestGameObject::init(){
        transformComponent->transform.pos = Float3(0.5f,0.2f,0.f);
        auto mc = std::make_shared<StaticMeshComponent>(this);
        mc->init();
        attachComponentTo(mc, getRootComponent(), "static_mesh");
        smc = mc.get();
    }
}