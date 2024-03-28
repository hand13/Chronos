#include "D3D11BaseRenderState.h"
namespace Chronos {

void D3D11BaseRenderState::setDirty(bool dirty) { this->dirty = dirty; }
bool D3D11BaseRenderState::isDirty() { return dirty; }
}  // namespace Chronos