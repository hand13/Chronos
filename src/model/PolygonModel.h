#pragma once
#include <memory>
#include <vector>
#include <render/VertexData.h>
namespace Chronos{
    typedef std::vector<std::shared_ptr<VertexData>> Meshes;
    class PolygonModel {
        private:
        Meshes meshes;
        public:
        Meshes& getMeshes();
    };
}