#pragma once
#include <memory>
#include <vector>
#include <render/BaseRenderableObject.h>
namespace Chronos{
    typedef std::vector<std::shared_ptr<BaseRenderableObject>> Meshes;
    class PolygonModel {
        private:
        Meshes meshes;
        public:
        Meshes& getMeshes();
    };
}