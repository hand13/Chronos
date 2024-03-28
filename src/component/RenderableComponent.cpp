#include "RenderableComponent.h"

#include <engine/Scene.h>

namespace Chronos {
void RenderableComponent::solve() {
    getGameObject()->getScene()->addRenderableComponent(this);
}
}  // namespace Chronos
