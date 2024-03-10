#pragma once
#include "base/Event.h"
#include "base/Utils.h"
#include "engine/Scene.h"
#include "render/Renderer.h"
#include "ResourceLoader.h"
#include "base/apidef.h"
#include <module/ModuleLoader.h>
#include <vector>
#include "EngineState.h"

namespace Chronos {
    class ChronosEngine {
        public:

        virtual void init(Renderer * renderer) = 0;
        virtual void begin() = 0;
        virtual void shutdown() = 0;
        virtual Renderer* getRenderer() = 0;
        virtual ResourceLoader * getResourceLoader() = 0;
        virtual void runInLoop() = 0;
        virtual void initSize(const SizeU& size)= 0;
        virtual void changeSize(const SizeU& size) = 0;
        virtual SizeU getSize()const = 0;
        virtual void setModuleLoader(ModuleLoader * ml) = 0;
        virtual EngineState getState() = 0;
        virtual void pushEvents(std::vector<IOEvent>& events) = 0;
        virtual Scene* getCurrentScene() = 0;
        protected:
        virtual void render() = 0;
        virtual void update() = 0;
        virtual ~ChronosEngine(){}
        public:
    };
    void MakeChronosGlobal(ChronosEngine* chronos);
    CHRONOS_API  ChronosEngine* Engine;
}