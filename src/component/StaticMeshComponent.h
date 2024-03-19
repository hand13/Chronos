#pragma once
#include "RenderableComponent.h"
#include <render/Material.h>
#include <render/PBRMaterial.h>
#include "render/PBRVertexProc.h"
#include "render/Texture2D.h"
#include "render/VertexProc.h"
#include <base/Transform.h>
#include <model/PolygonModel.h>
#include <memory>
#include <render/RenderConstantData.h>
namespace Chronos{
    class StaticMeshComponent:public RenderableComponent{
        private:

        std::shared_ptr<PolygonModel> pm;
        std::shared_ptr<Material> materil;
        std::shared_ptr<VertexProc> vproc;
        std::unique_ptr<RenderConstantData> rcd;
        std::shared_ptr<Texture2D> albedoTexture;
        std::shared_ptr<Texture2D> roughnessTexture;
        std::shared_ptr<Texture2D> metallicTexture;

        PBRVertexProc::PBRVertexConsData pbrVState;

        public:
        struct PBRState {
            PBRMaterial::PBRMaterialAttr attr;
            PBRMaterial::PBRMaterialLight light;
            PBRMaterial::PBRMaterialCamera camera;
        };
        PBRState pbrState;
        virtual void init() override;
        StaticMeshComponent(GameObject* gameObject):RenderableComponent(gameObject){}
        void feedRCDToPBRState();
        virtual void render(Renderer * renderer)override;
        Transform getTransform();
        virtual ~StaticMeshComponent(){}
    };
}