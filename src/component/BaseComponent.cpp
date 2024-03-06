#include "BaseComponent.h"
#include <Log.h>
namespace Chronos {
        BaseComponent::BaseComponent(GameObject * gameObject):gameObect(gameObject){
            parent = nullptr;
        }
        void BaseComponent::init(){
            //do nothing
        }

        GameObject* BaseComponent::getGameObject(){
            return gameObect;
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

        BaseComponent::~BaseComponent(){
            Log("Component destructed");
        }
}