#pragma once
#include <base/Utils.h>
#include <unordered_map>
#include <memory>
#include <string>
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
    typedef std::unordered_map<std::string,SlotAndRawData> RawDataMap;
    typedef std::unordered_map<std::string,SlotAndTexture> Texture2DMap;
    class RenderConstantData{
        private:
        RawDataMap vertexProcDataMap;
        RawDataMap materialDataMap;
        Texture2DMap textureMap;
        public:

        template<typename T>
        void setVertexProcData(const std::string& name,const T& value){
            vertexProcDataMap.at(name).rawData->copyIntoThis((const u8*)&value,0, 0,sizeof(T));
        }
        
        template<typename T>
        void setMaterialData(const std::string& name,const T& value){
            materialDataMap.at(name).rawData->copyIntoThis((const u8*)&value,0, 0,sizeof(T));
        }

        void setTexture(const std::string& name,std::shared_ptr<Texture2D> texture){
            textureMap.at(name).texture = texture;
        }

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