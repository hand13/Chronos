#pragma once
#include "Texture2D.h"

namespace Chronos {
class RenderTarget {
   public:
    virtual Texture2D* asTexture() = 0;
    virtual void* asTextureHandler() = 0;
    virtual ~RenderTarget() {}
};
};  // namespace Chronos