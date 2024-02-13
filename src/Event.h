#pragma once
namespace Chronos{
    enum IOEventType {
        NONE,
        MOUSE_MOVE,
        KEY_PRESSED,
        QUIT
    };
    enum Key {
        A,B,DOWN,UP,LEFT,RIGHT
    };
    struct IOEvent{
        IOEventType eventType;
        union{
            struct{
                int x;
                int y;
            } xy;
            Key key;
        }detail;
    };
}