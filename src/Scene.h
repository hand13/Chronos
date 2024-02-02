#pragma once
namespace Chronos {
    class Scene {
        public:
        virtual void init() = 0;
        virtual void begin() = 0;
        virtual void render() = 0;
        virtual void update() = 0;
        ~Scene();
    };
}