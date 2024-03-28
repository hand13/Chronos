#include "TestGameObject.h"

#include <cmath>
#include <memory>

#include "base/Utils.h"

namespace Chronos {
void TestGameObject::init() {
    transformComponent->transform.pos = Float3(0.0f, 0.f, 0.f);
    // transformComponent->transform.scale = Float3(3.f,3.f,3.f);
    auto mc = std::make_shared<StaticMeshComponent>(this);
    mc->init();
    attachComponentTo(mc, getRootComponent(), "static_mesh");
    smc = mc.get();
}
void TestGameObject::update(unsigned int delta) {
    static unsigned int es = 0;
    es += delta;
    float second = static_cast<float>(es) / 1000.f;
    float x = 4.f * sin(second);
    transformComponent->transform.pos.x = x;
    transformComponent->transform.rotation.x = second * 360.f;
}
}  // namespace Chronos