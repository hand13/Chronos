#include "ChronosD3D11Texture2D.h"
namespace Chronos {

void ChronosD3D11Texture2D::setSRV(ComPtr<ID3D11ShaderResourceView> _srv) {
    this->_srv = _srv;
}
ID3D11ShaderResourceView* ChronosD3D11Texture2D::getSRV() { return _srv.Get(); }
ChronosD3D11Texture2D::~ChronosD3D11Texture2D() {}
}  // namespace Chronos