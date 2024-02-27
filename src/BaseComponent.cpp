#include "BaseComponent.h"
namespace Chronos {
        BaseComponent::BaseComponent(){
            parent = nullptr;
        }
        void BaseComponent::init(){
            //do nothing
        }

        void BaseComponent::setParent(Component* parent){
            this->parent = parent;
        }
        Component* BaseComponent::getParent(){
            return parent;
        }
        void BaseComponent::solve(){
            // do nothing
        }
        void BaseComponent::setName(const std::string& name){
            this->name = name;
        }
        const std::string& BaseComponent::getName()const{
            return name;
        }
        std::vector<Component*>& BaseComponent::getChildren(){
            return children;
        }
        void BaseComponent::addComponent(Component* component){
            children.push_back(component);
        }
        void BaseComponent::destroy(){
            //do nothing
        }
}