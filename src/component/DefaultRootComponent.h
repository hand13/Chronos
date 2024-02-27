#pragma once
#include "BaseComponent.h"
namespace Chronos {
    class DefaultRootComponent:public BaseComponent {
        public:
        DefaultRootComponent(GameObject * gameObject):BaseComponent(gameObject){}
        virtual ~DefaultRootComponent(){}
    };
}