#pragma once
#include <memory>
#include <string>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "PolygonModel.h"
namespace Chronos {
    class PolygonModelLoader{
        private:
        Assimp::Importer importer;
        protected:
        void processNode(aiNode * node,const aiScene * scene,const std::string&dir,std::shared_ptr<PolygonModel>& target);
        void processMesh(aiMesh * mesh,const aiScene * scene,const std::string&dir,std::shared_ptr<PolygonModel>& target);
        public:
        PolygonModelLoader();
        public:
        std::shared_ptr<PolygonModel> loadPolygonModel(const std::string& path);
    };
}