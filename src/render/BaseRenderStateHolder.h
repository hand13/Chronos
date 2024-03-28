#pragma once
#include <memory>

#include "RenderStateHolder.h"
#include "render/RenderState.h"

namespace Chronos {
class BaseRenderStateHolder : public RenderStateHolder {
   protected:
    std::unique_ptr<RenderState> renderState;

   public:
    virtual void setRenderState(std::unique_ptr<RenderState>&& state) override;
    virtual RenderState* getRenderstate() override;
    virtual void cleanState() override;
    virtual ~BaseRenderStateHolder() {}
};
}  // namespace Chronos