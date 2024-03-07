#include "BaseChronosEngine.h"
#include "Log.h"
#include "Utils.h"
#include <memory>
#ifdef _WIN32
#include "platform/windows/render/d3d11/D3D11Renderer.h"
#endif
#include "imgui_control/TestUI.h"
#include "Log.h"
namespace Chronos {

    BaseChronosEngine::BaseChronosEngine(){
        enableImgui = false;
    }

    void BaseChronosEngine::init() {
        state = 1;
        option.renderType = 1;
        createRender();
        renderer->init();

        createWindow();
        window->init(renderer.get());
        window->getSize(windowSize.width,windowSize.height);

        
        if(enableImgui){
            cui = std::make_unique<TestUI>();
            cui->init(renderer.get());
        }

        initStartScene();
    }

    void BaseChronosEngine::changeSize(){
        mainScene->changeSize(windowSize);
    }

    void BaseChronosEngine::createWindow(){
        window = CreateWin();
    }

    void BaseChronosEngine::createRender(){
        if(option.renderType == 1){
            createD3D11Render();
        }else {
            Panic("not support");
        }
    }

    void BaseChronosEngine::createD3D11Render(){
        #ifdef _WIN32
        renderer = std::make_unique<D3D11Renderer>();
        #endif
        #ifndef _WIN32
        Panic("not support")
        #endif
    }

    ResourceLoader* BaseChronosEngine::getResourceLoader(){
        return &resourceLoader;
    }
    void BaseChronosEngine::shutdown() {
        state = 0;
    }

    Renderer* BaseChronosEngine::getRenderer(){
        return renderer.get();
    }
    ChronosWindow* BaseChronosEngine::getWindow() {
        return window.get();
    }

    void BaseChronosEngine::begin() {
        Log("game start");
        window->show();
        timer.start();
    }
    
    SizeU BaseChronosEngine::getWindowSize()const {
        return windowSize;
    }

    void BaseChronosEngine::loop() {
        while(state == 1){

            auto es = window->processEvent();
            for(auto & e : es){
                if(e.eventType == QUIT){
                    state = 0;
                }else {
                    mainScene->processEvent(e);
                }
            }
            if(state){
                SizeU tmpSize;
                window->getSize(tmpSize.width, tmpSize.height);
                if(tmpSize.width != windowSize.width || tmpSize.height != windowSize.height){
                    windowSize = tmpSize;
                    changeSize();
                }
                update();
                render();
                window->persent();
            }
            if(enableImgui){
                cui->displayOffscreen(mainScene->getRenderTargetAsTexture());
                cui->runInLoop();
            }
        }
    }

    void BaseChronosEngine::render(){
        mainScene->render();
        window->displayOffscreen(mainScene->getRenderTargetAsTexture());
    }

    void BaseChronosEngine::update() {
        mainScene->update(timer.delta());
    }

    BaseChronosEngine::~BaseChronosEngine() {
        Log("Engine destroyed");
    }
}