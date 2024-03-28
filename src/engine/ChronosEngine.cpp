#include "ChronosEngine.h"
namespace Chronos {
ChronosEngine* Engine = nullptr;
void MakeChronosGlobal(ChronosEngine* chronos) { Engine = chronos; }
}  // namespace Chronos