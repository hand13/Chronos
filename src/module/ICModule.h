#pragma once
#include "CModuleType.h"
namespace Chronos {
class ICModule {
   public:
    virtual CModuleType getType() const = 0;
    virtual const char* getName() const = 0;
    virtual const char* getDesc() const = 0;
    virtual ~ICModule() {}
};
}  // namespace Chronos