#pragma once
#include "RenderableComponent.h"
namespace Chronos{
    class StaticMeshComponent:public RenderableComponent{
        public:
        StaticMeshComponent(GameObject* gameObject):RenderableComponent(gameObject){}
        virtual ~StaticMeshComponent(){}
    };
}