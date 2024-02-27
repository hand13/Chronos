#include "BaseGameObject.h"
#include "Utils.h"
namespace Chronos {
    BaseGameObject::BaseGameObject(){
        root = nullptr;
    }
    void BaseGameObject::attachComponentTo(std::shared_ptr<Component>& component,Component* target,const std::string& componentName){
        if(components.find(componentName) != components.end()){
            Panic("已存在的组件名称");
        }
        //todo 确认组件树中是否存在target
        if(target != nullptr){
            target->addComponent(component.get());
        }else {
            if(root != nullptr){
                Panic("已存在root");
            }
            root = target;
        }
        components[componentName] = component;
        component->setName(componentName);
        component->setParent(target);
    }
    Component* BaseGameObject::getRootComponent(){
        return root;
    }
    Component* BaseGameObject::getComponent(const std::string& name){
        if(components.find(name) == components.end()){
            return nullptr;
        }
        return components.at(name).get();
    }
    void BaseGameObject::init(){
        //do nothing
    }
    void BaseGameObject::beginPlay(){
        //do nothing;
    }
    void BaseGameObject::update(){
        //do nothing
    }
    void BaseGameObject::destroy(){
        //do nothing
    }
}