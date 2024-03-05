#include "PolygonModelLoader.h"
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <exception>
#include <memory>
#include <utility>
#include <vector>
#include <render/DefaultMaterial.h>
#include <render/DefaultVetexProc.h>
namespace Chronos {

    PolygonModelLoader::PolygonModelLoader(){

    }

    std::shared_ptr<PolygonModel> PolygonModelLoader::loadPolygonModel(const std::string& path){
        std::shared_ptr<PolygonModel> result = std::make_shared<PolygonModel>();
        const aiScene * scene = importer.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs|aiProcess_GenNormals);
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            throw std::exception(importer.GetErrorString());
        }
        std::string dir = path.substr(0,path.find_last_of('/'));
        processNode(scene->mRootNode, scene,dir,result);
        return result;
    }

    void PolygonModelLoader::processNode(aiNode * node,const aiScene * scene,const std::string&dir,std::shared_ptr<PolygonModel>& target) {

        for(unsigned int i = 0;i <node->mNumMeshes;i++) {
            aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh,scene,dir,target);
        }
        for(unsigned int i =0;i<node->mNumChildren;i++) {
            processNode(node->mChildren[i],scene,dir,target);
        }

    }

    void PolygonModelLoader::processMesh(aiMesh * mesh,const aiScene * scene,const std::string&dir,std::shared_ptr<PolygonModel>& target) {
        Geometry::AttributeSet as;
        if(mesh->HasPositions()) {
            as.addAttribute("pos", Geometry::VEC);
        }
        if(mesh->HasTextureCoords(0)) {
            as.addAttribute("uv", Geometry::VEC2);
        }
        if(mesh->HasNormals()) {
            as.addAttribute("normal", Geometry::VEC);
        }
        size_t vertCompoentCount = as.totalSize()/sizeof(float);//一个顶点有多少个float数据

        std::vector<float> data(vertCompoentCount * mesh->mNumVertices);
        std::vector<int> indices;

        if(mesh->HasPositions()){
            size_t attr_offset = as.getAttributeOffset("pos")/sizeof(float);
            for(unsigned int i = 0;i<mesh->mNumVertices;i++) {
                unsigned int offset = static_cast<unsigned int>(i * vertCompoentCount + attr_offset);
                data[offset+0] = mesh->mVertices[i].x;
                data[offset+1] = mesh->mVertices[i].y;
                data[offset+2] = mesh->mVertices[i].z;
            }
        }

        if(mesh->HasTextureCoords(0)){
            size_t attr_offset = as.getAttributeOffset("uv")/sizeof(float);
            for(unsigned int i = 0;i<mesh->mNumVertices;i++) {
                unsigned int offset = static_cast<unsigned int>(i * vertCompoentCount + attr_offset);
                data[offset+0] = mesh->mTextureCoords[0][i].x;
                data[offset+1] = mesh->mTextureCoords[0][i].y;
            }
        }

        if(mesh->HasNormals()){
            size_t attr_offset = as.getAttributeOffset("normal")/sizeof(float);
            for(unsigned int i = 0;i<mesh->mNumVertices;i++) {
                unsigned int offset = static_cast<unsigned int>(i * vertCompoentCount + attr_offset);
                data[offset+0] = mesh->mNormals[i].x;
                data[offset+1] = mesh->mNormals[i].y;
                data[offset+2] = mesh->mNormals[i].z;
            }
        }
        for(size_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(size_t j = 0; j < face.mNumIndices; j++){
                indices.push_back(face.mIndices[j]);
            }
        }
        std::shared_ptr<BaseRenderableObject> bro = std::make_shared<BaseRenderableObject>();
        bro->setAttributeSet(as);
        bro->setIndices(std::move(indices));
        bro->setVertices(std::move(data));
        bro->setMaterial(std::make_unique<DefaultMaterial>());
        bro->setVertexProc(std::make_unique<DefaultVertexProc>());
        target->getMeshes().push_back(bro);

        // if(mesh->mMaterialIndex >= 0) {
        //     aiMaterial *amaterial = scene->mMaterials[mesh->mMaterialIndex];
        //     if(amaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0){
        //     aiString path;
        //     amaterial->GetTexture(aiTextureType_DIFFUSE,0, &path);
        //     std::filesystem::path p(path.C_Str());
        //     std::string true_path;
        //     if(p.is_absolute()){
        //         true_path = path.C_Str();
        //     }else {
        //         true_path = dir+"/" + path.C_Str();
        //     }
        //     m->diffuse_texture = World::rsLoader().getTexture(true_path);
        //     }
        //     int difcount = amaterial->GetTextureCount(aiTextureType_DIFFUSE);
        //     int specount = amaterial->GetTextureCount(aiTextureType_SPECULAR);

        //     if(amaterial->GetTextureCount(aiTextureType_SPECULAR) > 0){
        //         aiString path;
        //         amaterial->GetTexture(aiTextureType_SPECULAR,0, &path);
        //         std::filesystem::path p(path.C_Str());
        //         std::string true_path;
        //         if(p.is_absolute()){
        //             true_path = path.C_Str();
        //         }else {
        //             true_path = dir+"/" + path.C_Str();
        //         }
        //         m->specular_texture = World::rsLoader().getTexture(true_path);
        //     }

        //     material = m;
        // }
    }
}

