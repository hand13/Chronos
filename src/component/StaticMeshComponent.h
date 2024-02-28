#pragma once
#include "RenderableComponent.h"
#include "../render/BaseRenderableObject.h"
namespace Chronos{
    class StaticMeshComponent:public RenderableComponent{
        private:
        BaseRenderableObject bro;
        public:
        virtual void init() override;
        StaticMeshComponent(GameObject* gameObject):RenderableComponent(gameObject){}
        virtual void render(Renderer * renderer)override;
        virtual ~StaticMeshComponent(){}
    };
}