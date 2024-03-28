#pragma once
#include <memory>
#include <vector>

#include "base/Event.h"
#include "render/Renderer.h"

namespace Chronos {
class ChronosWindow {
   public:
    virtual void getSize(unsigned int& w, unsigned int& h) = 0;
    virtual void init(Renderer* renderer) = 0;
    virtual void show() = 0;
    virtual std::vector<IOEvent> processEvent() = 0;
    virtual void displayOffscreen(void* thandler) = 0;
    virtual void persent() = 0;
    virtual void captureCursor() = 0;
    virtual void releaseCursor() = 0;
    virtual ~ChronosWindow() {}
};
std::unique_ptr<ChronosWindow> CreateWin();
}  // namespace Chronos