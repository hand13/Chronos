#include "D3D11RendererModule.h"

#include "render/Renderer.h"

namespace Chronos {
D3D11RendererModule::D3D11RendererModule() {
    type = RENDERER;
    name = "d3d11 renderer";
    desc = "d3d11 renderer module";
}
CModuleType D3D11RendererModule::getType() const { return type; }
const char* D3D11RendererModule::getName() const { return name.c_str(); }
const char* D3D11RendererModule::getDesc() const { return desc.c_str(); }
Renderer* D3D11RendererModule::getRenderer() { return &renderer; }
}  // namespace Chronos
