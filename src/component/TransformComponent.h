#pragma once
#include "BaseComponent.h"
#include "../Transform.h"
namespace Chronos{
    class TransformComponent :public BaseComponent{
        public:
        Transform transform;
        virtual ~TransformComponent(){}
    };
}