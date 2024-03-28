#pragma once
#include <Windows.h>
#include <base/Event.h>
#include <base/Utils.h>

#include <vector>

namespace Chronos {
class EventBridge {
   private:
    std::vector<IOEvent> events;
    RectU rect;
    bool focused;

   public:
    EventBridge() { focused = false; }
    inline const std::vector<IOEvent>& getEvents() const { return events; };
    inline void setRect(const RectU& rect) { this->rect = rect; }

    inline void focus() { focused = true; }
    inline void unFocus() { focused = false; }
    inline bool isFocused() { return focused; }

    bool inRect(const MSG& msg);

    bool shouldProcessMsg(const MSG& msg);

    void pushMSG(const MSG& msg);
    inline void clean() { events.clear(); }
};
}  // namespace Chronos