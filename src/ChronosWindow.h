#pragma once
#include <memory>
namespace Chronos {
    class ChronosWindow {
        public:
        virtual void getSize(unsigned int& w,unsigned int & h) = 0;
        virtual void init() = 0;
        virtual void show() = 0;
        virtual void loop() = 0;
        virtual ~ChronosWindow(){}
    };
    std::unique_ptr<ChronosWindow> CreateWin();
}