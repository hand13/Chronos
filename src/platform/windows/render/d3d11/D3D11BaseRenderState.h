#pragma once
#include <render/RenderState.h>
namespace Chronos {
class D3D11BaseRenderState : public RenderState {
   protected:
    bool dirty;

   public:
    D3D11BaseRenderState() : dirty(true) {}
    virtual void setDirty(bool dirty) override;
    virtual bool isDirty() override;
    virtual ~D3D11BaseRenderState() {}
};
};  // namespace Chronos