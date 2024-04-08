#ifndef ENGINE_IO
#define ENGINE_IO
#pragma once

namespace EngineIO
{
    enum InputEvent
    {
        NONE = 0,
        RIGHT = 1,
        LEFT = 2,
        UP = 3,
        DOWN = 4,
        BACKSPACE = 8,
        TAB = 9,
        ENTER = 13,
        MOUSE_HOVER = 16,
        MOUSE_LEFT = 17,
        MOUSE_MIDDLE = 18,
        MOUSE_RIGHT = 19,
        MOUSE_SCROLL_UP = 20,
        MOUSE_SCROLL_DOWN = 21,
        ESC = 27,
        SHIFT = 28,
        CTRL = 29,
        ALT = 30,
        SPACE = 32,
        _1 = 49,
        _2 = 50,
        _3 = 51,
        _4 = 52,
        _5 = 53,
        _6 = 54,
        _7 = 55,
        _8 = 56,
        _9 = 57,
        _0 = 48,
        W = 119,
        A = 97,
        S = 115,
        D = 100,
        DEL = 127,
        F1 = 256,
        F2 = 257,
        F3 = 258,
        F4 = 259,
        F5 = 260,
        F6 = 261,
        F7 = 262,
        F8 = 263,
        F9 = 264,
        F10 = 265,
        F11 = 266,
        F12 = 267,
        NUM_SLASH = 268,
        NUM_ASTERISK = 269,
        NUM_MINUS = 270,
        NUM_PLUS = 271,
        NUM_ENTER = 272,
        NUM_1 = 273,
        NUM_2 = 274,
        NUM_3 = 275,
        NUM_4 = 276,
        NUM_5 = 277,
        NUM_6 = 278,
        NUM_7 = 279,
        NUM_8 = 280,
        NUM_9 = 281,
        NUM_0 = 282,
        NUM_POINT = 283
    };

    inline InputEvent charToInputEvent(char c)
    {
        return static_cast<InputEvent>(c);
    }

}

#endif // ENGINE_IO