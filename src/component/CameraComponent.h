#pragma once
#include "BaseComponent.h"
#include <Camera.h>
namespace Chronos {
    class CameraComponent:public BaseComponent{
        public:
        CameraComponent(GameObject * gameObject):BaseComponent(gameObject){}
        Camera camera;
        virtual ~CameraComponent(){}
    };
}