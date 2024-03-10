#include "BaseChronosEngine.h"
#include "base/Event.h"
#include "base/Log.h"
#include "base/Utils.h"
#include <memory>
#include "base/Log.h"
#include "engine/EngineState.h"
#include "render/Renderer.h"
namespace Chronos {

    BaseChronosEngine::BaseChronosEngine(){
        state = WAIT_INIT;
    }

    void BaseChronosEngine::setModuleLoader(ModuleLoader * ml){
    }
    void BaseChronosEngine::init(Renderer * renderer) {
        option.renderType = 1;
        this->renderer = renderer;
        initStartScene();
        state = RUNNING;
    }

    void BaseChronosEngine::initSize(const SizeU& size){
        this->size = size;
    }

    void BaseChronosEngine::changeSize(const SizeU& size){
        this->size = size;
        mainScene->changeSize(size);
    }

    ResourceLoader* BaseChronosEngine::getResourceLoader(){
        return &resourceLoader;
    }
    void BaseChronosEngine::shutdown() {
        state = STOP;
    }

    Renderer* BaseChronosEngine::getRenderer(){
        return renderer;
    }

    void BaseChronosEngine::begin() {
        Log("engine start");
        // window->show();
        timer.start();
    }
    
    SizeU BaseChronosEngine::getSize()const {
        return size;
    }

    void BaseChronosEngine::runInLoop() {
        if(state == RUNNING){
            for(auto & e : events){
                if(e.eventType == QUIT){
                    state = STOP;
                }else {
                    mainScene->processEvent(e);
                }
            }
            events.clear();
            if(state == RUNNING){
                update();
                render();
            }
        }
    }

    void BaseChronosEngine::render(){
        mainScene->render();
    }

    void BaseChronosEngine::update() {
        mainScene->update(timer.delta());
    }

    EngineState BaseChronosEngine::getState(){
        return state;
    }
    void BaseChronosEngine::pushEvents(std::vector<IOEvent>& es){
        events.insert(events.end(),es.begin(),es.end());
    }

    Scene* BaseChronosEngine::getCurrentScene() {
        return mainScene.get();
    }
    BaseChronosEngine::~BaseChronosEngine() {
        Log("Engine destroyed");
    }
}