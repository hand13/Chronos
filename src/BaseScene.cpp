#include "BaseScene.h"
#include "Chronos.h"
#include <cmath>
#include <vector>
namespace Chronos {

    BaseScene::BaseScene(){
        lastMouseX = 0;
        lastMouseY = 0;
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
        std::vector<float> vertices = {
            -1.f,0.f,-1.f,0,0,
            1.f,0.f,1.f,1.f,1.f,
            1.f,0.f,-1.f,1.f,0,

            -1.f,0.f,-1.f,0,0,
            -1.f,0.f,1.f,0,1.f,
            1.f,0.f,1.f,1.f,1.f,
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

    void BaseScene::processEvent(const IOEvent& event){
        if(event.eventType == MOUSE_MOVE){
            if(lastMouseX == 0 && lastMouseY == 0){
                lastMouseX = event.detail.xy.x;
                lastMouseY = event.detail.xy.y;
                return;
            }
            int deltaX = event.detail.xy.x - lastMouseX;
            int deltaY = event.detail.xy.y - lastMouseY;

            lastMouseX = event.detail.xy.x;
            lastMouseY = event.detail.xy.y;

            float yawSpeed = 0.1;
            float deltaYaw = static_cast<float>(deltaX) * yawSpeed;
            camera.addYaw(deltaYaw);
            float pitchSpeed = 0.1;
            float deltaPitch = static_cast<float>(deltaY) * pitchSpeed;
            camera.addPitch(-deltaPitch);
        }
        if(event.eventType == KEY_PRESSED){
            if(event.detail.key == DOWN){
                camera.moveForward(-0.1f);
            }else if(event.detail.key == UP){
                camera.moveForward(0.1f);
            }else if(event.detail.key == RIGHT) {
                camera.moveRight(0.1f);
            }else if(event.detail.key == LEFT) {
                camera.moveRight(-0.1f);
            }
        }
    }

    void BaseScene::update(){
    }
    BaseScene::~BaseScene(){
    }
}