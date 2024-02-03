#include "BaseScene.h"
#include "Chronos.h"
namespace Chronos {

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
        Renderer * render = Chronos::INSTANCE->getRender();
        rt = render->createRenderTarget();
    }

    void BaseScene::begin(){
    }
    void BaseScene::render(){
    }
    void BaseScene::update(){
    }
    BaseScene::~BaseScene(){
    }
}