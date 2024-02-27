#pragma once
#include "Component.h"
#include <vector>
#include "../game_object/GameObject.h"
namespace Chronos {
    class BaseComponent:public Component {
        std::string name;
        Component * parent;
        std::vector<Component*> children;
        GameObject* gameObect;
        public:
        BaseComponent(GameObject* gameObject);
        virtual GameObject* getGameObject()override;
        virtual void init()override;
        virtual void setParent(Component* parent)override;
        virtual Component* getParent()override;
        virtual void solve()override;
        virtual void setName(const std::string& name)override;
        virtual const std::string& getName()const override;
        virtual std::vector<Component*>& getChildren()override;

        virtual void addComponent(Component* component)override;

        virtual void destroy()override;
        virtual ~BaseComponent(){}
    };
}