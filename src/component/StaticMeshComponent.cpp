#include "StaticMeshComponent.h"

#include <engine/ChronosEngine.h>
#include <engine/Scene.h>

#include <memory>

#include "TransformComponent.h"
#include "base/Camera.h"
#include "base/Utils.h"
#include "render/PBRMaterial.h"
#include "render/PBRVertexProc.h"
#include "render/RenderConstantData.h"
#include "render/Texture.h"

namespace Chronos {
void StaticMeshComponent::init() {
    pm = Engine->getResourceLoader()->loadPolygonModelFromFile(
        "resources/models/test.fbx");

    albedoTexture = Engine->getResourceLoader()->loadTexture2D(
        "resources/textures/test_albedo.png", TextureParameter());
    metallicTexture = Engine->getResourceLoader()->loadTexture2D(
        "resources/textures/test_metallic.png", TextureParameter());
    roughnessTexture = Engine->getResourceLoader()->loadTexture2D(
        "resources/textures/test_roughness.png", TextureParameter());

    materil = std::make_shared<PBRMaterial>();
    vproc = std::make_shared<PBRVertexProc>();
    rcd = std::make_unique<RenderConstantData>(*vproc->getShaderConfig(),
                                               *materil->getShaderConfig());

    pbrState.attr = {.albedo = Float3(0.f, 0.f, 0.f),
                     .metallic = 0.0f,
                     .roughness = 0.0f,
                     .ao = 0.1f};
    pbrState.light = {.lightPosition = Float3(0, 2.f, 0.3f),
                      .lightColor = Float3(20.f, 20.f, 20.f)};
    pbrState.camera = {.cameraPos = Float3(0, 4.f, 0)};
}
void StaticMeshComponent::render(Renderer* renderer) {
    feedRCDToPBRState();
    for (auto m : pm->getMeshes()) {
        Matrix4f modelMatrix = getTransform().getMatrix();
        Matrix4f normMatrix = modelMatrix.inverse().transpose();

        pbrVState.modelMatrix = modelMatrix;
        pbrVState.normalMatrix = normMatrix;

        Camera& camera = this->getGameObject()->getScene()->getActiveCamera();
        pbrState.camera.cameraPos = camera.getPos();

        feedRCDToPBRState();
        renderer->render(*m, *vproc, *materil, *rcd);
    }
}
Transform StaticMeshComponent::getTransform() {
    TransformComponent* tc = dynamic_cast<TransformComponent*>(
        getGameObject()->getComponent("transform"));
    if (tc == nullptr) {
        Panic("should not happened");
    }
    return tc->transform;
}
void StaticMeshComponent::feedRCDToPBRState() {
    rcd->setVertexProcData("consData", pbrVState);
    rcd->setMaterialData("attr", pbrState.attr);
    rcd->setMaterialData("camera", pbrState.camera);
    rcd->setMaterialData("light", pbrState.light);
    rcd->setTexture("albedo_texture", albedoTexture);
    rcd->setTexture("metallic_texture", metallicTexture);
    rcd->setTexture("roughness_texture", roughnessTexture);
}
}  // namespace Chronos
