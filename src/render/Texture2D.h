#pragma once
#include "Texture.h"
namespace Chronos {
class Texture2D : public Texture {
   public:
    unsigned int width;
    unsigned int height;
    virtual ~Texture2D() {}
};
}  // namespace Chronos