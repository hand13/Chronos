#pragma once
#include <render/Renderer.h>

#include "BaseComponent.h"

namespace Chronos {
class RenderableComponent : public BaseComponent {
   public:
    RenderableComponent(GameObject* gameObject) : BaseComponent(gameObject) {}
    virtual void render(Renderer* renderer) = 0;
    virtual void solve() override;
    virtual ~RenderableComponent() {}
};
}  // namespace Chronos