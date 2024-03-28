#include "Asset.h"
namespace Chronos {

std::string assetIdToStr(AssetID assetId) { return ""; }

Asset::Asset(AssetID id, AssetType type) : assetID(id), assetType(type) {}
AssetID Asset::genAssetID() { return 0; }
}  // namespace Chronos