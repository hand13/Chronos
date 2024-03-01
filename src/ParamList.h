#pragma once
#include <map>
#include <string>
#include <vector>
#include "Param.h"
#include "GenericParam.hpp"
namespace Chronos {
    class ParamList{
        protected:
        std::vector<Param*> params;
        std::map<std::string,unsigned int> paramIndex;
        void destroyParams();
        public:
        ParamList();
        void registerParam(const std::string& name,ParamType type,size_t rawDataSize = 0);
        bool checkParam(const std::string& paramName,const ParamSignature& ps)const;
        Param* getParam(const std::string& name);
        const std::vector<Param*>& getParamList()const;
        template<typename T>
        void setParamValue(const std::string& name,const T& value){
            ParamSignature ps(FetchType<T>()(),sizeof(T));
            if(!checkParam(name, ps)){
                Panic("no such param");
            }
            GenericParam<T>& gp = dynamic_cast<GenericParam<T>&>(*getParam(name));
            gp.value = value;
        }
        ~ParamList();
    };
};