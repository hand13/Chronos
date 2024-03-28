#pragma once
#include <memory>

#include "RenderState.h"

namespace Chronos {
class RenderStateHolder {
   public:
    virtual void setRenderState(std::unique_ptr<RenderState>&& state) = 0;
    virtual RenderState* getRenderstate() = 0;
    virtual void cleanState() = 0;
    virtual ~RenderStateHolder() {}
};
}  // namespace Chronos