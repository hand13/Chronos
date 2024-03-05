#pragma once
#include "render/Renderer.h"
#include "ChronosWindow.h"
#include "ResourceLoader.h"

namespace Chronos {
    class ChronosEngine {
        public:

        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void shutdown() = 0;
        virtual Renderer* getRenderer() = 0;
        virtual ChronosWindow* getWindow() = 0;
        virtual ResourceLoader * getResourceLoader() = 0;
        virtual void loop() = 0;
        virtual SizeU getWindowSize()const = 0;

        protected:
        virtual void render() = 0;
        virtual void update() = 0;
        virtual ~ChronosEngine(){}
        public:
    };
    void MakeChronosGlobal(ChronosEngine* chronos);
    extern ChronosEngine* Engine;
}