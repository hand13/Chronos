#include "BaseScene.h"
#include "Chronos.h"
#include <vector>
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
        std::vector<float> vertices = {
            -1.f,-1.f,0,0,0,
            1.f,1.f,0,1.f,1.f,
            1.f,-1.f,0,1.f,0,

            -1.f,-1.f,0,0,0,
            -1.f,1.f,0,0,1.f,
            1.f,1.f,0,1.f,1.f,
        };
        robj.setVertices(vertices);
        Geometry::AttributeSet as;
        as.addAttribute("pos", Geometry::VEC);
        as.addAttribute("uv", Geometry::VEC2);

        robj.setAttributeSet(as);

    }
    void BaseScene::initRenderState(){
        Renderer * render = Chronos::INSTANCE->getRender();
        rt = render->createRenderTarget(Chronos::INSTANCE->getWindowSize());
        rc.setRenderTarget(rt.get());

        SizeU size = Chronos::INSTANCE->getWindowSize();
        camera.setWidth(size.width);
        camera.setHeight(size.height);

        rc.setCamera(&camera);
    }

    void BaseScene::changeSize(const SizeU& windowSize){
        rt = Chronos::INSTANCE->getRender()->createRenderTarget(windowSize);
        rc.setRenderTarget(rt.get());
        camera.setWidth(windowSize.width);
        camera.setHeight(windowSize.height);
        rc.setCamera(&camera);
    }

    void BaseScene::begin(){
    }
    void BaseScene::render(){
        Renderer * render = Chronos::INSTANCE->getRender();
        render->setRenderContext(&rc);
        render->beginRender();
        render->renderBaseRenderableObject(&robj);
        render->endRender();
    }

    void BaseScene::update(){
    }
    BaseScene::~BaseScene(){
    }
}