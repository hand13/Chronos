#include "ChronosWindow.h"

#include "platform/windows/window/d3d11/WinChronosWindow.h"

namespace Chronos {
std::unique_ptr<ChronosWindow> CreateWin() {
#ifdef _WIN32
    return std::make_unique<WinChronosWindow>();
#endif
    return nullptr;
}
}  // namespace Chronos
