#include "BaseChronos.h"
#include "Log.h"
namespace Chronos {
    void BaseChronos::init() {
        state = 1;
        createWindow();
        createRenderState();
        initStartScene();
        window->init();
    }

    void BaseChronos::createWindow(){
        window = CreateWin();
    }

    void BaseChronos::createRenderState(){
        if(option.renderType == 1){
            createD3D11RenderState();
        }
    }

    void BaseChronos::createD3D11RenderState(){
        #ifdef _WIN32
        #endif
    }

    void BaseChronos::shutdown() {
        state = 0;
    }

    ChronosWindow* BaseChronos::getWindow() {
        return window.get();
    }

    Renderer* BaseChronos::getRender(){
        return renderer.get();
    }

    void BaseChronos::begin() {
        Log("game start");
        window->show();
    }
    
    void BaseChronos::loop() {
        while(state == 1){
            window->loop();
            update();
            render();
        }
    }

    void BaseChronos::render(){
        mainScene->render();
        window->displayOffscreen(mainScene->getRenderTarget());
    }

    void BaseChronos::update() {
        mainScene->update();
    }
    BaseChronos::~BaseChronos() {
    }
}