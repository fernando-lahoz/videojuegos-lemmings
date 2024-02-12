#pragma once

namespace EngineIO
{
    enum InputEvent
    {
        NONE=0,
        RIGHT_ARROW=1,
        LEFT_ARROW=2,
        UP_ARROW=4,
        DOWN_ARROW=8,
        W=16,
        A=32,
        S=64,
        D=128,
        SPACE=256,
        SHIFT=512,
        CTRL=1024,
        ALT=2048,
        ENTER=4096,
        ESC=8192,
        TAB=16384,
        BACKSPACE=32768,
        MOUSE_HOVER=65536,
        MOUSE_LEFT=131072,
        MOUSE_RIGHT=262144,
        MOUSE_MIDDLE=524288,
        MOUSE_SCROLL_UP=1048576,
        MOUSE_SCROLL_DOWN=2097152
    };
}