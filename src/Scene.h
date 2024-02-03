#pragma once
#include "render/RenderTarget.h"
namespace Chronos {
    class Scene {
        public:
        virtual RenderTarget* getRenderTarget() = 0;
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        ~Scene();
    };
}