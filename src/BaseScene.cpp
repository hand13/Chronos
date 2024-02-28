#include "BaseScene.h"
#include "Chronos.h"
#include <memory>
#include <utility>
#include <vector>
namespace Chronos {

    BaseScene::BaseScene():activeCamera(defaultCamera){
        lastMouseX = 0;
        lastMouseY = 0;
        lButtonPressed = false;
        shouldInitMousePos = true;
        objectCounts = 0;
    }

    Camera& BaseScene::getActiveCamera(){
        return activeCamera;
    }
    void BaseScene::setActiveCamera(Camera& camera){
        activeCamera = camera;
    }

    RenderTarget* BaseScene::getRenderTarget(){
        return rt.get();
    }
    Texture2D* BaseScene::getRenderTargetAsTexture(){
        return rt->asTexture();
    }

    void BaseScene::init(){
        initRenderState();
        initScene();

    }
    void BaseScene::initRenderState(){
        Renderer * render = Chronos::INSTANCE->getRenderer();
        rt = render->createRenderTarget(Chronos::INSTANCE->getWindowSize());
        rc.setRenderTarget(rt.get());

        SizeU size = Chronos::INSTANCE->getWindowSize();
        activeCamera.setWidth(size.width);
        activeCamera.setHeight(size.height);

        rc.setCamera(&activeCamera);
        rc.setFXAA(true);
    }

    void BaseScene::changeSize(const SizeU& windowSize){
        rt = Chronos::INSTANCE->getRenderer()->createRenderTarget(windowSize);
        rc.setRenderTarget(rt.get());
        activeCamera.setWidth(windowSize.width);
        activeCamera.setHeight(windowSize.height);
        rc.setCamera(&activeCamera);
    }

    void BaseScene::begin(){
    }
    void BaseScene::render(){
        Renderer * renderer = Chronos::INSTANCE->getRenderer();
        renderer->setRenderContext(&rc);
        renderer->beginRender();

        /**
        * @brief 渲染所用RenderableComponent
        * 
        * @param rc:rcs 
        */
        for(auto rc:rcs){
            rc->render(renderer);
        }
        cleanRenderableComponent();

        renderer->endRender();
    }

    void BaseScene::processEvent(const IOEvent& event){
        if(event.eventType == MOUSE_MOVE && lButtonPressed){

            if(shouldInitMousePos){
                lastMouseX = event.detail.xy.x;
                lastMouseY = event.detail.xy.y;
                shouldInitMousePos = false;
                return;
            }

            int deltaX = event.detail.xy.x - lastMouseX;
            int deltaY = event.detail.xy.y - lastMouseY;

            lastMouseX = event.detail.xy.x;
            lastMouseY = event.detail.xy.y;

            float yawSpeed = 0.3;
            float deltaYaw = static_cast<float>(deltaX) * yawSpeed;
            activeCamera.addYaw(deltaYaw);
            float pitchSpeed = 0.3;
            float deltaPitch = static_cast<float>(deltaY) * pitchSpeed;
            activeCamera.addPitch(-deltaPitch);
        }
        if(event.eventType == KEY_PRESSED){
            if(event.detail.key == CHVK_DOWN || event.detail.key == CHVK_S){
                activeCamera.moveForward(-0.1f);
            }else if(event.detail.key == CHVK_UP || event.detail.key == CHVK_W){
                activeCamera.moveForward(0.1f);
            }else if(event.detail.key == CHVK_RIGHT || event.detail.key == CHVK_D) {
                activeCamera.moveRight(0.1f);
            }else if(event.detail.key == CHVK_LEFT || event.detail.key == CHVK_A) {
                activeCamera.moveRight(-0.1f);
            }else if(event.detail.key == CHVK_LBUTTON){
                lButtonPressed = true;
            }
        }
        if(event.eventType == kEY_RELEASED){
            if(event.detail.key == CHVK_LBUTTON){
                lButtonPressed = false;            }
                shouldInitMousePos = true;
        }
    }

    void BaseScene::update(){
        solveAllComponents();
    }

    bool BaseScene::containObject(const std::string& name)const {
        return gameObjectMap.find(name) != gameObjectMap.end();
    }
    GameObject* BaseScene::getGameObject(const std::string& name){
        if(!containObject(name)){
            return nullptr;
        }
        return gameObjectMap[name].get();
    }

    std::map<std::string,std::shared_ptr<GameObject>>& BaseScene::getAllGameObjects() {
        return gameObjectMap;
    }

    void BaseScene::addGameObject(std::shared_ptr<GameObject> go,const std::string& name){
        if(containObject(name)){
            Panic(name+":this name has been used");
        }
        gameObjectMap[name] = go;
    }

    void BaseScene::solveAllComponents(){
        for(auto go : gameObjectMap){
            solveGameObjectComponent(go.second.get());
        }
    }

    void BaseScene::solveGameObjectComponent(GameObject * gameObject){
        Component* root = gameObject->getRootComponent();
        if(root != nullptr){
            solveComponent(root);
        }
    }

    void BaseScene::solveComponent(Component* component){
        if(component != nullptr){
            component->solve();
        }
        for(auto child:component->getChildren()){
            solveComponent(child);
        }
    }

    void BaseScene::addRenderableComponent(RenderableComponent* renderableComponent){
        rcs.push_back(renderableComponent);
    }

    void BaseScene::cleanRenderableComponent(){
        rcs.clear();
    }

    BaseScene::~BaseScene(){
    }
}