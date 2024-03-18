#include "BaseRenderStateHolder.h"
#include <utility>
namespace Chronos{
    void BaseRenderStateHolder::setRenderState(std::unique_ptr<RenderState>&& state){
        renderState = std::move(state);
    }
    RenderState * BaseRenderStateHolder::getRenderstate(){
        return renderState.get();
    }
    void BaseRenderStateHolder::cleanState(){
        renderState = nullptr;
    }
}
