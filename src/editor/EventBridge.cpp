#include "EventBridge.h"
namespace Chronos {

bool EventBridge::inRect(const MSG& msg) {
    u32 x = static_cast<u32>(LOWORD(msg.lParam));
    u32 y = static_cast<u32>(HIWORD(msg.lParam));
    return x > rect.left && x < rect.right && y > rect.top && y < rect.bottom;
}

bool EventBridge::shouldProcessMsg(const MSG& msg) {
    switch (msg.message) {
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
            return inRect(msg);
        case WM_KEYUP:
        case WM_KEYDOWN:
            return isFocused();
        default:
            return false;
    }
}
void EventBridge::pushMSG(const MSG& msg) {
    if (!shouldProcessMsg(msg)) {
        return;
    }

    switch (msg.message) {
        case WM_MOUSEMOVE: {
            int x = LOWORD(msg.lParam);
            int y = HIWORD(msg.lParam);
            IOEvent e;
            e.eventType = MOUSE_MOVE;
            e.detail.xy = {.x = x, .y = y};
            events.push_back(e);
            break;
        }
        case WM_LBUTTONDOWN: {
            IOEvent e;
            e.eventType = KEY_PRESSED;
            e.detail.key = CHVK_LBUTTON;
            events.push_back(e);
            break;
        }
        case WM_LBUTTONUP: {
            IOEvent e;
            e.eventType = kEY_RELEASED;
            e.detail.key = CHVK_LBUTTON;
            events.push_back(e);
            break;
        }

        case WM_KEYUP: {
            IOEvent e;
            e.eventType = kEY_RELEASED;
            e.detail.key = (VirtualKey)msg.wParam;
            events.push_back(e);
            break;
        }
        case WM_KEYDOWN: {
            IOEvent e;
            e.eventType = KEY_PRESSED;
            e.detail.key = (VirtualKey)msg.wParam;
            events.push_back(e);
            break;
        }
        default:
            break;
    }
}
}  // namespace Chronos