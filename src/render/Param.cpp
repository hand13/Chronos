#include "Param.h"
namespace Chronos {

    ParamType IntParam::type(){
        return ParamType::INT;
    }
    IntParam::IntParam(int value){
        this->value = value;
    }
}
