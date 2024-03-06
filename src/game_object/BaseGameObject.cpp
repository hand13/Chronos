#include "BaseGameObject.h"
#include <Utils.h>
#include <memory>
#include <component/DefaultRootComponent.h>
#include <Log.h>
namespace Chronos {
    BaseGameObject::BaseGameObject(Scene * scene){
        root = nullptr;
        this->scene = scene;
        attachComponentTo(std::make_shared<DefaultRootComponent>(this),nullptr, "root");
        auto tc = std::make_shared<TransformComponent>(this);
        transformComponent = tc.get();
        attachComponentTo(tc, root, "transform");
    }
    void BaseGameObject::attachComponentTo(std::shared_ptr<Component> component,Component* target,const std::string& componentName){
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
            root = component.get();
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

    Scene* BaseGameObject::getScene(){
        return scene;
    }

    void BaseGameObject::init(){
        //do nothing
    }
    void BaseGameObject::beginPlay(){
        //do nothing;
    }
    void BaseGameObject::update(unsigned int delta){
        //do nothing
    }
    void BaseGameObject::destroy(){
        //do nothing
    }
    BaseGameObject::~BaseGameObject(){
        Log("GameObject destructed");
    }
}