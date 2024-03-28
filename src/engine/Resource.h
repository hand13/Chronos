#pragma once
#include "base/BaseTypes.h"
typedef u64 ResId;
class Resource {
   public:
    virtual ResId getResId() = 0;
    virtual ~Resource() {}
};