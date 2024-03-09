#include "StaticMeshComponent.h"
#include "base/Camera.h"
#include "TransformComponent.h"
#include "base/Utils.h"
#include <ChronosEngine.h>
#include <Scene.h>
namespace Chronos{
    void StaticMeshComponent::init(){
        pm = Engine->getResourceLoader()->loadPolygonModelFromFile("resources/models/box.fbx");
    }
    void StaticMeshComponent::render(Renderer * renderer){

        for(auto m : pm->getMeshes()){
            
            Matrix4f modelMatrix = getTransform().getMatrix();
            Matrix4f normMatrix = modelMatrix.inverse().transpose();
            m->getVertexProc()->getShaderConfig()->getParamList().setParamValue("model_matrix",modelMatrix);
            m->getVertexProc()->getShaderConfig()->getParamList().setParamValue("normal_matrix",normMatrix);
            Camera& camera = this->getGameObject()->getScene()->getActiveCamera();
            m->getMaterial()->getShaderConfig()->getParamList().setParamValue("camPos",camera.getPos());
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
