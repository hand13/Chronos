#pragma once
#include "BaseComponent.h"
#include <render/Renderer.h>
namespace Chronos{
    class RenderableComponent:public BaseComponent{
        public:
        RenderableComponent(GameObject * gameObject):BaseComponent(gameObject){}
        virtual void render(Renderer * renderer) = 0;
        virtual void solve()override;
        virtual ~RenderableComponent(){}
    };
}