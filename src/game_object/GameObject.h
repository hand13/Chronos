#pragma once
#include <component/Component.h>

#include <memory>
#include <string>

namespace Chronos {
/**
 * @brief component 生命周期由gameobject控制
 *
 */
class Scene;
class GameObject {
   public:
    virtual void init() = 0;
    virtual void beginPlay() = 0;
    virtual void update(unsigned int delta) = 0;
    virtual Scene* getScene() = 0;
    /**
     * @brief
     * 附加组件
     * @param component 需要附加的组件
     * @param target 为null时即为root
     * @param componentName 组件名称
     */
    virtual void attachComponentTo(std::shared_ptr<Component> component,
                                   Component* target,
                                   const std::string& componentName) = 0;
    virtual Component* getRootComponent() = 0;
    virtual Component* getComponent(const std::string& name) = 0;
    virtual void destroy() = 0;
    virtual ~GameObject() {}
};
};  // namespace Chronos