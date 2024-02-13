#pragma once
#include "VK.h"
namespace Chronos{
    enum IOEventType {
        MOUSE_MOVE,
        KEY_PRESSED,
        kEY_RELEASED,
        QUIT,
    };
    struct IOEvent{
        IOEventType eventType;
        union{
            struct{
                int x;
                int y;
            } xy;
            VirtualKey key;
        }detail;
    };
}