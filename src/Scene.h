#pragma once
#include "render/RenderTarget.h"
#include "render/Texture2D.h"
#include "Utils.h"
#include "Event.h"
namespace Chronos {
    class Scene {
        public:
        virtual RenderTarget* getRenderTarget() = 0;
        virtual Texture2D* getRenderTargetAsTexture() = 0;
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void processEvent(const IOEvent& event) = 0;
        virtual void changeSize(const SizeU& windowSize) = 0;
        virtual ~Scene(){};
    };
}