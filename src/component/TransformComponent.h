#pragma once
#include "BaseComponent.h"
#include <base/Transform.h>
namespace Chronos{
    class TransformComponent :public BaseComponent{
        public:
        TransformComponent(GameObject* gameObject):BaseComponent(gameObject){}
        Transform transform;
        virtual ~TransformComponent(){}
    };
}