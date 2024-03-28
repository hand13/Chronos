#pragma once
#include <base/Camera.h>

#include "BaseComponent.h"

namespace Chronos {
class CameraComponent : public BaseComponent {
   public:
    CameraComponent(GameObject* gameObject) : BaseComponent(gameObject) {}
    Camera camera;
    virtual ~CameraComponent() {}
};
}  // namespace Chronos