#include "StaticMeshComponent.h"
#include "TransformComponent.h"
#include <Chronos.h>
namespace Chronos{
    void StaticMeshComponent::init(){
        pm = Chronos::INSTANCE->getResourceLoader()->loadPolygonModelFromFile("resources/models/test.fbx");
    }
    void StaticMeshComponent::render(Renderer * renderer){
        for(auto m : pm->getMeshes()){
            m->getVertexProc()->getShaderConfig()->getParamList().setParamValue("model_matrix",getTransform().getMatrix());
            renderer->renderBaseRenderableObject(m.get());
        }
    }
    Transform StaticMeshComponent::getTransform(){
        TransformComponent * tc = dynamic_cast<TransformComponent*>(getGameObject()->getComponent("transform"));
        if(tc == nullptr){
            Panic("should not happened");
        }
        return tc->transform;
    }
}
