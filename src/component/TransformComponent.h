#pragma once
#include "BaseComponent.h"
#include <Transform.h>
namespace Chronos{
    class TransformComponent :public BaseComponent{
        public:
        TransformComponent(GameObject* gameObject):BaseComponent(gameObject){}
        Transform transform;
        virtual ~TransformComponent(){}
    };
}