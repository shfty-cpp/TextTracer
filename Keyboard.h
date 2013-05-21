#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

struct Keyboard
{
    static bool IsKeyDown(char key)
    {
#ifdef _WIN32
        return GetAsyncKeyState(key);
#endif
    }
};

#endif // KEYBOARD_H
