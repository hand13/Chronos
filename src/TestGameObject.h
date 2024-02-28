#pragma once
#include "game_object/BaseGameObject.h"
#include "component/StaticMeshComponent.h"
namespace Chronos {
    class TestGameObject:public BaseGameObject{
        private:
        StaticMeshComponent * smc;
        public:
        TestGameObject(Scene* scene):BaseGameObject(scene),smc(nullptr){};
        virtual void init()override;
        virtual void update(unsigned int delta)override;
        virtual ~TestGameObject(){}
    };
}