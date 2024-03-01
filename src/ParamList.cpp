#include "ParamList.h"
#include <cstddef>
namespace Chronos {

    void ParamList::destroyParams(){
        for(int i =0;i<params.size();i++){
            if(params[i]){
                delete params[i];
            }
            params[i] = 0;
        }
    }
    ParamList::ParamList(){
    }
    void ParamList::registerParam(const std::string& name,ParamType type,size_t rawDataSize){
        Param* res = constructParamFromType(name,type,rawDataSize);
        params.push_back(res);
        paramIndex[name] = static_cast<unsigned int>(params.size()-1);
    }

    bool ParamList::checkParam(const std::string& paramName,const ParamSignature& ps)const{
        return paramIndex.find(paramName) != paramIndex.end() && params[paramIndex.at(paramName)]->signature() == ps;
    }

    Param* ParamList::getParam(const std::string& name){
        if(paramIndex.find(name) == paramIndex.end()){
            return nullptr;
        }
        return params[paramIndex.at(name)];
    }

    const std::vector<Param*>& ParamList::getParamList()const{
        return params;
    }
    ParamList::~ParamList(){
        destroyParams();
    }
}