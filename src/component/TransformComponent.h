#pragma once
#include <base/Transform.h>

#include "BaseComponent.h"

namespace Chronos {
class TransformComponent : public BaseComponent {
   public:
    TransformComponent(GameObject* gameObject) : BaseComponent(gameObject) {}
    Transform transform;
    virtual ~TransformComponent() {}
};
}  // namespace Chronos