#pragma once
#include <memory>
#include "render/Texture2D.h"
namespace Chronos {
    class ChronosWindow {
        public:
        virtual void getSize(unsigned int& w,unsigned int & h) = 0;
        virtual void init() = 0;
        virtual void show() = 0;
        virtual bool processEvent() = 0;
        virtual void displayOffscreen(Texture2D * rt) = 0;
        virtual void persent();
        virtual ~ChronosWindow(){}
    };
    std::unique_ptr<ChronosWindow> CreateWin();
}