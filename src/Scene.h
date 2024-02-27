#pragma once
#include "render/RenderTarget.h"
#include "render/Texture2D.h"
#include "Utils.h"
#include "Event.h"
#include "GameObject.h"
#include <map>
#include <memory>
namespace Chronos {
    typedef std::map<std::string, std::shared_ptr<GameObject>> GameObjectMap;
    class Scene {
        public:
        virtual RenderTarget* getRenderTarget() = 0;
        virtual Texture2D* getRenderTargetAsTexture() = 0;
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void processEvent(const IOEvent& event) = 0;
        virtual void changeSize(const SizeU& windowSize) = 0;

        virtual bool containObject(const std::string& name)const = 0;
        virtual GameObject* getGameObject(const std::string& name) = 0;
        virtual GameObjectMap& getAllGameObjects() = 0;

        virtual ~Scene(){};
    };
}