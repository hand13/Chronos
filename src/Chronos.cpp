#include "Chronos.h"
namespace Chronos{
    Chronos* Chronos::INSTANCE = nullptr;
    void Chronos::MakeChronosGlobal(Chronos* chronos) {
        INSTANCE = chronos;
    }
}