#pragma once
#include "render/RenderTarget.h"
#include "render/Texture2D.h"
namespace Chronos {
    class Scene {
        public:
        virtual RenderTarget* getRenderTarget() = 0;
        virtual Texture2D* getRenderTargetAsTexture() = 0;
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual ~Scene(){};
    };
}