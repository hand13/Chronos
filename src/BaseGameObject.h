#pragma once
#include "GameObject.h"
#include <memory>
#include <string>
#include <map>
namespace Chronos{
    class BaseGameObject:public GameObject {
        private:
        std::map<std::string,std::shared_ptr<Component>> components;
        Component * root;
        public:
        BaseGameObject();
        virtual void init()override;
        virtual void beginPlay()override;
        virtual void update()override;
        virtual void attachComponentTo(std::shared_ptr<Component>& component,Component* target,const std::string& componentName)override;
        virtual Component* getRootComponent()override;
        virtual Component* getComponent(const std::string& name)override;
        virtual void destroy()override;
        virtual ~BaseGameObject(){}
    };
}