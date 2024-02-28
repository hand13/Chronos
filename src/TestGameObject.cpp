#include "TestGameObject.h"
#include <memory>
namespace Chronos{
    void TestGameObject::init(){
        auto mc = std::make_shared<StaticMeshComponent>(this);
        mc->init();
        attachComponentTo(mc, getRootComponent(), "static_mesh");
        smc = mc.get();
    }
}