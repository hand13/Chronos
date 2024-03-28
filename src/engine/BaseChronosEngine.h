#pragma once
#include <memory>
#include <vector>

#include "ChronosEngine.h"
#include "Option.h"
#include "Scene.h"
#include "base/Event.h"
#include "base/Timer.h"
#include "base/Utils.h"
#include "engine/EngineState.h"
#include "render/Renderer.h"

namespace Chronos {
class BaseChronosEngine : public ChronosEngine {
   protected:
    Timer timer;
    std::unique_ptr<Scene> mainScene;
    Renderer* renderer;

    EngineState state;
    Option option;
    ResourceLoader resourceLoader;
    SizeU size;
    std::vector<IOEvent> events;

   public:
    BaseChronosEngine();
    virtual void init(Renderer* renderer) override;
    virtual void begin() override;
    virtual void runInLoop() override;
    virtual void shutdown() override;
    virtual void setModuleLoader(ModuleLoader* ml) override;
    virtual ResourceLoader* getResourceLoader() override;

    virtual Renderer* getRenderer() override;
    virtual void changeSize(const SizeU& size) override;
    virtual SizeU getSize() const override;
    virtual EngineState getState() override;
    virtual void pushEvents(std::vector<IOEvent>& events) override;
    virtual Scene* getCurrentScene() override;
    virtual void initSize(const SizeU& size) override;

   protected:
    virtual void initStartScene() = 0;
    virtual void render() override;
    virtual void update() override;
    virtual ~BaseChronosEngine();
};
}  // namespace Chronos