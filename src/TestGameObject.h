#pragma once
#include "component/StaticMeshComponent.h"
#include "game_object/BaseGameObject.h"

namespace Chronos {
class TestGameObject : public BaseGameObject {
   private:
    StaticMeshComponent* smc;

   public:
    TestGameObject(Scene* scene) : BaseGameObject(scene), smc(nullptr){};
    virtual void init() override;
    virtual void update(unsigned int delta) override;
    virtual ~TestGameObject() {}
};
}  // namespace Chronos