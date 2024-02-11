#include "RenderContext.h"
namespace Chronos {
    RenderContext::RenderContext(){
        camera = nullptr;
        rtv = nullptr;
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
}