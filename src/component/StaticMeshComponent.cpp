#include "StaticMeshComponent.h"
#include "TransformComponent.h"
#include "../Chronos.h"
namespace Chronos{
    void StaticMeshComponent::init(){
        pm = Chronos::INSTANCE->getResourceLoader()->loadPolygonModelFromFile("resources/models/test.fbx");
        // std::vector<float> vertices = {
        //     -1.f,1.f,-1.f,0,0,
        //     1.f,1.f,1.f,1.f,1.f,
        //     1.f,1.f,-1.f,1.f,0,

        //     -1.f,1.f,-1.f,0,0,
        //     -1.f,1.f,1.f,0,1.f,
        //     1.f,1.f,1.f,1.f,1.f,

        //     -1.f,-1.f,-1.f,0,0,
        //     1.f,-1.f,-1.f,1.f,0,
        //     1.f,-1.f,1.f,1.f,1.f,

        //     -1.f,-1.f,-1.f,0,0,
        //     1.f,-1.f,1.f,1.f,1.f,
        //     -1.f,-1.f,1.f,0,1.f,

        //     -1.f,-1.f,1.f,0,0,
        //     1.f,-1.f,1.f,1.f,0,
        //     1.f,1.f,1.f,1.f,1.f,

        //     -1.f,-1.f,1.f,0,0,
        //     1.f,1.f,1.f,1.f,1.f,
        //     -1.f,1.f,1.f,0.f,1.f,

        //     -1.f,-1.f,-1.f,0,0,
        //     1.f,1.f,-1.f,1.f,1.f,
        //     1.f,-1.f,-1.f,1.f,0,

        //     -1.f,-1.f,-1.f,0,0,
        //     -1.f,1.f,-1.f,0.f,1.f,
        //     1.f,1.f,-1.f,1.f,1.f,

        //     -1.f,-1.f,-1.f,0,0,
        //     -1.f,1.f,1.f,1.f,1.f,
        //     -1.f,1.f,-1.f,1.f,0,

        //     -1.f,-1.f,-1.f,0,0,
        //     -1.f,-1.f,1.f,0.f,1.f,
        //     -1.f,1.f,1.f,1.f,1.f,

        //     1.f,-1.f,-1.f,0,0,
        //     1.f,1.f,-1.f,1.f,0,
        //     1.f,1.f,1.f,1.f,1.f,

        //     1.f,-1.f,-1.f,0,0,
        //     1.f,1.f,1.f,1.f,1.f,
        //     1.f,-1.f,1.f,0.f,1.f,

        // };

        // bro.setVertices(vertices);
        // Geometry::AttributeSet as;
        // as.addAttribute("pos", Geometry::VEC);
        // as.addAttribute("uv", Geometry::VEC2);

        // bro.setAttributeSet(as);
        // std::unique_ptr<Material> material = std::make_unique<DefaultMaterial>();
        // std::unique_ptr<VertexProc> vertexProc = std::make_unique<DefaultVertexProc>();
        // bro.setMaterial(std::move(material));
        // bro.setVertexProc(std::move(vertexProc));
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
