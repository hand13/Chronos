#include "RenderConstantData.h"
#include "base/Utils.h"
#include "render/ShaderConfig.h"
#include <memory>
namespace Chronos{
    RenderConstantData::RenderConstantData(const ShaderConfig& vsc,const ShaderConfig& msc){
        for(auto& vdef : vsc.getConstantDataDef()){
            vertexProcDataMap[vdef.name] = SlotAndRawData{.rawData = std::make_shared<RawData>(vdef.size),.slot = vdef.slot};
        }
        for(auto& mdef : msc.getConstantDataDef()){
            if(mdef.type == CDT_Texture2D){
                textureMap[mdef.name] = SlotAndTexture{.texture = nullptr,.slot = mdef.slot};
            }else {
                materialDataMap[mdef.name] = SlotAndRawData{.rawData = std::make_shared<RawData>(mdef.size),.slot = mdef.slot};
            }
        }
    }
}