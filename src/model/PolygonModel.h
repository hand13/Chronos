#pragma once
#include <render/VertexData.h>

#include <memory>
#include <vector>

namespace Chronos {
typedef std::vector<std::shared_ptr<VertexData>> Meshes;
class PolygonModel {
   private:
    Meshes meshes;

   public:
    Meshes& getMeshes();
};
}  // namespace Chronos