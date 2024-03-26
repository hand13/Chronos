#pragma once
#include "render/RenderTarget.h"
#include "render/Texture2D.h"
#include "base/Utils.h"
#include "base/Event.h"
#include "game_object/GameObject.h"
#include <map>
#include <memory>
#include "base/Camera.h"
#include "component/RenderableComponent.h"
namespace Chronos {
    typedef std::map<std::string, std::shared_ptr<GameObject>> GameObjectMap;
    enum SceneState {
        SC_UNINITED,
        SC_READY,
        SC_RUNNING,
        SC_PAUSED,
    };

    class Scene {
        public:
        virtual Camera& getActiveCamera() = 0;
        virtual void setActiveCamera(Camera& camera) =0;
        virtual RenderTarget* getRenderTarget() = 0;
        virtual Texture2D* getRenderTargetAsTexture() = 0;
        virtual void* getRenderTargetTextureHandler() = 0;
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void pause() = 0;
        virtual void resume() = 0;
        virtual SceneState getState()const = 0;
        /**
         * @brief 
         * 
         * @param deltaTime 毫秒
         */
        virtual void update(unsigned int deltaTime) = 0;
        virtual void processEvent(const IOEvent& event) = 0;
        virtual void changeSize(const SizeU& windowSize) = 0;

        virtual bool containObject(const std::string& name)const = 0;
        virtual GameObject* getGameObject(const std::string& name) = 0;
        virtual GameObjectMap& getAllGameObjects() = 0;

        /**
         * @brief 
         * 添加需要渲染的组件
         * @param renderableComponent 
         */

        virtual void addRenderableComponent(RenderableComponent* renderableComponent) = 0;
        /**
         * @brief 
         * 清空所用已渲染的组件
         */
        virtual void cleanRenderableComponent() = 0;

        virtual ~Scene(){};
    };
}