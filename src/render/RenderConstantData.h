#pragma once
#include <base/Utils.h>
#include <map>
#include <memory>
#include "Texture2D.h"
#include "Texture2D.h"
#include "ShaderConfig.h"
namespace Chronos {

    struct SlotAndRawData {
        std::shared_ptr<RawData> rawData;
        u8 slot;
    };
    struct SlotAndTexture {
        std::shared_ptr<Texture2D> texture;
        u8 slot;
    };
    typedef std::map<std::string,SlotAndRawData> RawDataMap;
    typedef std::map<std::string,SlotAndTexture> Texture2DMap;
    class RenderConstantData{
        private:
        RawDataMap vertexProcDataMap;
        RawDataMap materialDataMap;
        Texture2DMap textureMap;
        public:
        RenderConstantData(const ShaderConfig& vsc,const ShaderConfig& msc);
        inline const RawDataMap& getVertexProcDataMap()const{
            return vertexProcDataMap;
        };
        inline const RawDataMap& getMaterialDataMap()const{
            return materialDataMap;
        }
        inline const Texture2DMap& getTextureMap()const{
            return textureMap;
        }
        inline RawDataMap& getVertexProcDataMap(){
            return vertexProcDataMap;
        };
        inline RawDataMap& getMaterialDataMap(){
            return materialDataMap;
        }
        inline Texture2DMap& getTextureMap(){
            return textureMap;
        }
    };
}