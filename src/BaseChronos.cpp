#include "BaseChronos.h"
#include "Log.h"
#include "Utils.h"
#include <memory>
#ifdef _WIN32
#include "render/d3d11/D3D11Renderer.h"
#endif
namespace Chronos {

    BaseChronos::BaseChronos(){
    }

    void BaseChronos::init() {
        state = 1;
        option.renderType = 1;
        createWindow();
        window->init();
        window->getSize(windowSize.width,windowSize.height);
        createRender();
        renderer->init();
        initStartScene();
    }

    void BaseChronos::changeSize(){
        mainScene->changeSize(windowSize);
    }

    void BaseChronos::createWindow(){
        window = CreateWin();
    }

    void BaseChronos::createRender(){
        if(option.renderType == 1){
            createD3D11Render();
        }
    }

    void BaseChronos::createD3D11Render(){
        #ifdef _WIN32
        renderer = std::make_unique<D3D11Renderer>();
        #endif
        #ifndef _WIN32
        Panic("not support")
        #endif
    }

    ResourceLoader* BaseChronos::getResourceLoader(){
        return &resourceLoader;
    }
    void BaseChronos::shutdown() {
        state = 0;
    }

    Renderer* BaseChronos::getRender(){
        return renderer.get();
    }
    ChronosWindow* BaseChronos::getWindow() {
        return window.get();
    }

    void BaseChronos::begin() {
        Log("game start");
        window->show();
    }
    
    SizeU BaseChronos::getWindowSize()const {
        return windowSize;
    }

    void BaseChronos::loop() {
        while(state == 1){
            if(window->processEvent()){

                SizeU tmpSize;
                window->getSize(tmpSize.width, tmpSize.height);
                if(tmpSize.width != windowSize.width || tmpSize.height != windowSize.height){
                    windowSize = tmpSize;
                    changeSize();
                }

                update();
                render();

                window->persent();
            }else{
                state = 0;
            }
        }
    }

    void BaseChronos::render(){
        mainScene->render();
        window->displayOffscreen(mainScene->getRenderTargetAsTexture());
    }

    void BaseChronos::update() {
        mainScene->update();
    }
    BaseChronos::~BaseChronos() {
    }
}