#include "BaseChronosEngine.h"
#include "base/Log.h"
#include "base/Utils.h"
#include <memory>
#include "base/Log.h"
#include "module/ICModule.h"
#include "module/IRendererModule.h"
namespace Chronos {

    BaseChronosEngine::BaseChronosEngine(){
        enableImgui = true;
        rendererModule = nullptr;
    }

    void BaseChronosEngine::setModuleLoader(ModuleLoader * ml){
        moduleLoader = ml;
    }
    void BaseChronosEngine::init() {
        if(moduleLoader == nullptr){
            Panic("please set a moduleLoader");
        }
        state = 1;
        option.renderType = 1;
        createRender();
        renderer->init();

        createWindow();
        window->init(renderer);
        window->getSize(windowSize.width,windowSize.height);

        
        if(enableImgui){
            ced= std::make_unique<ChronosEditor>();
            ced->init(renderer);
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
        ICModule * im =  moduleLoader->installModule("d3d11_renderer.dll");
        rendererModule = nullptr;
        if(im &&(rendererModule = dynamic_cast<IRendererModule*>(im))){
            renderer = rendererModule->getRenderer();
        }else{
            Panic("not a renderer");
        }
        // renderer = std::make_unique<D3D11Renderer>();
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
        return renderer;
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
                ced->setScene(mainScene.get());
                ced->displayOffscreen(mainScene->getRenderTargetTextureHandler());
                ced->runInLoop();
            }
        }
    }

    void BaseChronosEngine::render(){
        mainScene->render();
        window->displayOffscreen(mainScene->getRenderTargetTextureHandler());
    }

    void BaseChronosEngine::update() {
        mainScene->update(timer.delta());
    }


    BaseChronosEngine::~BaseChronosEngine() {
        Log("Engine destroyed");
    }
}