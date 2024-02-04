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
        rc.setRenderTarget(rt.get());

        ChronosWindow * wc = Chronos::INSTANCE->getWindow();
        unsigned int w,h;
        wc->getSize(w, h);

        camera.setWidth(w);
        camera.setHeight(h);

        rc.setCamera(&camera);
    }

    void BaseScene::begin(){
    }
    void BaseScene::render(){
        Renderer * render = Chronos::INSTANCE->getRender();
        render->setRenderContext(&rc);
        render->beginRender();
        render->endRender();
    }

    void BaseScene::update(){
    }
    BaseScene::~BaseScene(){
    }
}