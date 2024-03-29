#pragma once
#include <component/TransformComponent.h>
#include <engine/Scene.h>

#include <map>
#include <memory>
#include <string>

#include "GameObject.h"

namespace Chronos {
class BaseGameObject : public GameObject {
   protected:
    std::map<std::string, std::shared_ptr<Component>> components;
    Component* root;
    TransformComponent* transformComponent;
    Scene* scene;

   public:
    BaseGameObject(Scene* scene);
    virtual Scene* getScene() override;
    virtual void init() override;
    virtual void beginPlay() override;
    virtual void update(unsigned int delta) override;
    virtual void attachComponentTo(std::shared_ptr<Component> component,
                                   Component* target,
                                   const std::string& componentName) override;
    virtual Component* getRootComponent() override;
    virtual Component* getComponent(const std::string& name) override;
    virtual void destroy() override;
    virtual ~BaseGameObject();
};
}  // namespace Chronos