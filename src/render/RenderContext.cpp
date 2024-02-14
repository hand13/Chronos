#include "RenderContext.h"
namespace Chronos {
    RenderContext::RenderContext(){
        camera = nullptr;
        rtv = nullptr;
        useFXAA = false;
    }
    void RenderContext::setCamera(Camera* camera){
        this->camera = camera;
    }
    void RenderContext::setRenderTarget(RenderTarget* rtv){
        this->rtv = rtv;
    }
    Camera* RenderContext::getCamera(){
        return camera;
    }

    RenderTarget* RenderContext::getRenderTarget(){
        return rtv;
    }
    void RenderContext::setFXAA(bool useFXAA){
        this->useFXAA = useFXAA;
    }
    bool RenderContext::shouldUseFXAA(){
        return useFXAA;
    }
}