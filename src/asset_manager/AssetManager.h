#pragma once
#include <memory>

#include "asset_manager/IAssetLoader.h"

namespace Chronos {
class AssetManager {
   public:
    AssetManager();
    void loadAssetManifest(const char* manifestPath);
    void registerAssetLoader(std::shared_ptr<IAssetLoader> assetLoader);
};
}  // namespace Chronos