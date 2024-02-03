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
        createRender();
        initStartScene();
        window->init();
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
    
    void BaseChronos::loop() {
        while(state == 1){
            if(window->processEvent()){
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