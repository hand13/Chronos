#pragma once
#include "Scene.h"
#include <memory>
#include <string>
#include "render/RenderContext.h"
#include "render/BaseRenderableObject.h"

namespace Chronos {
    class BaseScene:public Scene{
        protected:
        GameObjectMap gameObjectMap;
        std::unique_ptr<RenderTarget> rt;
        BaseRenderableObject robj;
        RenderContext rc;
        Camera camera;
        unsigned int objectCounts;

        int lastMouseX;
        int lastMouseY;
        bool lButtonPressed;
        bool shouldInitMousePos;

        virtual void init()override;
        virtual void initRenderState();
        virtual void initScene() = 0;
        virtual void solveAllComponents();
        void addGameObject(std::shared_ptr<GameObject> go,const std::string& name);
        private:
        void solveGameObjectComponent(GameObject * gameObject);
        public:
        BaseScene();
        virtual RenderTarget* getRenderTarget()override;
        virtual Texture2D* getRenderTargetAsTexture()override;
        virtual void begin()override;
        virtual void render()override;
        virtual void update()override;
        virtual void processEvent(const IOEvent& event)override;
        virtual void changeSize(const SizeU& windowSize)override;

        virtual GameObject* getGameObject(const std::string& name)override;
        virtual GameObjectMap& getAllGameObjects() override;

        virtual bool containObject(const std::string& name)const override;

        template<typename T,typename ... types>
        T* spawnObject(const std::string& name,types&& ... args) {
            std::shared_ptr<T> result = std::make_shared<T>(this,std::forward<types>(args)...);
            std::string n;
            n = name;
            if(name == "") {
                    std::string un = "unknown";
                    n = std::string("unknown") + std::to_string(objectCounts);
                    objectCounts++;
            }
            addGameObject(result,n);
            return result.get();
        }

        virtual ~BaseScene();
    };
}