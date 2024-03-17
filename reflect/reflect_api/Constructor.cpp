#include "Constructor.h"

bool Constructor::checkParams(CallParams& pms){
    if(pms.size() != params.size()){
        return false;
    }
    int i = 0;
    for(auto & cp :pms){
        if(cp.klass != params[i].type.klass){
            return false;
        }
    }
    return true;
}