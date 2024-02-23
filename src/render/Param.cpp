#include "Param.h"
namespace Chronos {

    Geometry::Type IntParam::type(){
        return Geometry::INT;
    }
    IntParam::IntParam(int value){
        this->value = value;
    }
}
