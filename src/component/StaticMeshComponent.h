#pragma once
#include "RenderableComponent.h"
#include "../Transform.h"
#include "../model/PolygonModel.h"
#include <memory>
namespace Chronos{
    class StaticMeshComponent:public RenderableComponent{
        private:
        std::shared_ptr<PolygonModel> pm;
        public:
        virtual void init() override;
        StaticMeshComponent(GameObject* gameObject):RenderableComponent(gameObject){}
        virtual void render(Renderer * renderer)override;
        Transform getTransform();
        virtual ~StaticMeshComponent(){}
    };
}