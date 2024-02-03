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
    const Camera* RenderContext::getCamera()const{
        return camera;
    }
    const RenderTarget* RenderContext::getRenderTarget()const{
        return rtv;
    }
}