#pragma once
#include <base/BaseTypes.h>

#include <any>
#include <map>
#include <string>

#include "AssetType.h"

namespace Chronos {
typedef u64 AssetID;
std::string assetIdToStr(AssetID assetId);
typedef std::map<std::string, std::any> Params;
class Asset {
   private:
    AssetID assetID;
    AssetType assetType;
    Params params;

   public:
    Asset(AssetID id, AssetType type);
    inline AssetID getId() { return assetID; }
    inline AssetType getAssetType() { return assetType; };
    inline const Params& getParams() const { return params; };
    inline Params& getParams() { return params; };
    static AssetID genAssetID();
};
}  // namespace Chronos