#pragma once
#include "RenderableComponent.h"
#include "../render/BaseRenderableObject.h"
#include "../Transform.h"
namespace Chronos{
    class StaticMeshComponent:public RenderableComponent{
        private:
        BaseRenderableObject bro;
        ParamList* vParamList;
        public:
        virtual void init() override;
        StaticMeshComponent(GameObject* gameObject):RenderableComponent(gameObject),vParamList(nullptr){}
        virtual void render(Renderer * renderer)override;
        Transform getTransform();
        virtual ~StaticMeshComponent(){}
    };
}