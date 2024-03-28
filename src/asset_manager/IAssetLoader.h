#pragma once
#include "Asset.h"
#include "asset_manager/AssetType.h"
namespace Chronos {
class IAssetLoader {
   public:
    virtual AssetType getAssetType() = 0;
    virtual Asset loadAsset(AssetID assetID) = 0;
    virtual Asset loadAsset(const char* path) = 0;
    virtual void persistentAsset(const Asset& asset, const char* path) = 0;
    virtual ~IAssetLoader() {}
};
}  // namespace Chronos