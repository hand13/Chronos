#pragma once
#include <render/Renderer.h>

#include "ICModule.h"

namespace Chronos {
class IRendererModule : public ICModule {
   public:
    virtual CModuleType getType() const = 0;
    virtual const char* getName() const = 0;
    virtual const char* getDesc() const = 0;
    virtual Renderer* getRenderer() = 0;
    virtual ~IRendererModule() {}
};
}  // namespace Chronos