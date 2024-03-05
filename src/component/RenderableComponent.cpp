#include "RenderableComponent.h"
#include <Scene.h>
namespace Chronos{
    void RenderableComponent::solve(){
        getGameObject()->getScene()->addRenderableComponent(this);
    }
}
