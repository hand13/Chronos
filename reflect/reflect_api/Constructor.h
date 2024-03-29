#pragma once
#include <exception>
#include <string>
#include <vector>

#include "Access.h"
#include "CallParam.h"
#include "MetaInfo.h"
#include "MethodParam.h"


/**
 * @brief 构造器
 *
 */
struct Constructor {
    Access access;
    std::string name;
    MetaInfo metaInfo;
    /**
     * @brief 参数
     *
     */
    std::vector<MethodParam> params;

   public:
    Constructor() { fc = nullptr; }
    inline void setFunCall(FunCall fc) { this->fc = fc; }

    template <typename T>
    T* newInstance(CallParams& pms, bool checkWithKlass = true) {
        if (!checkParams(pms)) {
            throw std::exception("illegal params");
        }
        return reinterpret_cast<T*>(fc(pms));
    }

   private:
    FunCall fc;
    bool checkParams(CallParams& pms);
};