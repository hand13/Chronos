#include <module/IRendererModule.h>

#include "D3D11Renderer.h"
#include "module/CModuleType.h"

namespace Chronos {
class D3D11RendererModule : public IRendererModule {
   private:
    CModuleType type;
    D3D11Renderer renderer;
    std::string name;
    std::string desc;

   public:
    D3D11RendererModule();
    virtual CModuleType getType() const override;
    virtual const char* getName() const override;
    virtual const char* getDesc() const override;
    virtual Renderer* getRenderer() override;
    virtual ~D3D11RendererModule() {}
};
}  // namespace Chronos