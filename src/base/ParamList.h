#pragma once
#include <cstddef>
#include <map>
#include <string>
#include <vector>
#include "Param.h"
#include "GenericParam.hpp"
#include "Utils.h"
namespace Chronos {
    class ParamList{
        protected:
        std::vector<Param*> params;
        std::map<std::string,unsigned int> paramIndex;
        std::map<u8,u16> slotAndSize;
        // std::vector<std::pair<u8,u16>> slotAndSize;
        void destroyParams();
        std::map<std::string,u16> offset_data;
        void appendPackInfo(const std::string& paramName,size_t size,PackInfo packInfo);
        public:
        ParamList();
        /**
         * @brief 注册参数
         * 
         * @param name 
         * @param type 
         * @param packInfo 可选,为零时自动打包
         * @param rawDataSize 可选
         */
        void registerParam(const std::string& name,ParamType type,PackInfo packInfo = 0,size_t rawDataSize = 0);
        /**
         * @brief 检查参数是否合法
         * 
         * @param paramName 
         * @param ps 
         * @return true 
         * @return false 
         */
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
        /**
         * @brief 根据PackInfo打包数据
         * 
         * @param slot 
         * @return RawData 
         */
        RawData packDataInSlot(u8 slot);
        /**
         * @brief Get the All Slot Size
         * 
         * @return std::vector<size_t> 
         */
        const std::map<u8,u16>& getAllSlotAndSize()const;
        u8 getTexturesCount();
        ~ParamList();
    };
};