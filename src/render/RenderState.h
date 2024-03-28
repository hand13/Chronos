#pragma once
#include "RenderConstantData.h"
namespace Chronos {
class RenderState {
   public:
    virtual void setDirty(bool dirty) = 0;
    virtual bool isDirty() = 0;
    virtual void update() = 0;
    virtual void applyWith(const RenderConstantData& rcd) = 0;
    virtual ~RenderState() {}
};
}  // namespace Chronos