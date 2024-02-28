#include "StaticMeshComponent.h"
#include "../render/DefaultMaterial.h"
#include "../render/DefaultVetexProc.h"
namespace Chronos{
    void StaticMeshComponent::init(){
        std::vector<float> vertices = {
            -1.f,1.f,-1.f,0,0,
            1.f,1.f,1.f,1.f,1.f,
            1.f,1.f,-1.f,1.f,0,

            -1.f,1.f,-1.f,0,0,
            -1.f,1.f,1.f,0,1.f,
            1.f,1.f,1.f,1.f,1.f,

            -1.f,-1.f,-1.f,0,0,
            1.f,-1.f,-1.f,1.f,0,
            1.f,-1.f,1.f,1.f,1.f,

            -1.f,-1.f,-1.f,0,0,
            1.f,-1.f,1.f,1.f,1.f,
            -1.f,-1.f,1.f,0,1.f,

            -1.f,-1.f,1.f,0,0,
            1.f,-1.f,1.f,1.f,0,
            1.f,1.f,1.f,1.f,1.f,

            -1.f,-1.f,1.f,0,0,
            1.f,1.f,1.f,1.f,1.f,
            -1.f,1.f,1.f,0.f,1.f,

            -1.f,-1.f,-1.f,0,0,
            1.f,1.f,-1.f,1.f,1.f,
            1.f,-1.f,-1.f,1.f,0,

            -1.f,-1.f,-1.f,0,0,
            -1.f,1.f,-1.f,0.f,1.f,
            1.f,1.f,-1.f,1.f,1.f,

            -1.f,-1.f,-1.f,0,0,
            -1.f,1.f,1.f,1.f,1.f,
            -1.f,1.f,-1.f,1.f,0,

            -1.f,-1.f,-1.f,0,0,
            -1.f,-1.f,1.f,0.f,1.f,
            -1.f,1.f,1.f,1.f,1.f,

            1.f,-1.f,-1.f,0,0,
            1.f,1.f,-1.f,1.f,0,
            1.f,1.f,1.f,1.f,1.f,

            1.f,-1.f,-1.f,0,0,
            1.f,1.f,1.f,1.f,1.f,
            1.f,-1.f,1.f,0.f,1.f,

        };

        bro.setVertices(vertices);
        Geometry::AttributeSet as;
        as.addAttribute("pos", Geometry::VEC);
        as.addAttribute("uv", Geometry::VEC2);

        bro.setAttributeSet(as);
        std::unique_ptr<Material> material = std::make_unique<DefaultMaterial>();
        std::unique_ptr<VertexProc> vertexProc = std::make_unique<DefaultVertexProc>();
        bro.setMaterial(std::move(material));
        bro.setVertexProc(std::move(vertexProc));
    }
    void StaticMeshComponent::render(Renderer * renderer){
        renderer->renderBaseRenderableObject(&bro);
    }
}
