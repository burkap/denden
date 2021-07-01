#pragma once
#include <renderer.h>
#include <keycodes.h>

class Input
{
    static Input* instance;
    static GLFWwindow* window;
public:
    Input();
    static bool is_key_down(int KEYCODE);
    static void set_window(GLFWwindow* w);

    static Input* the();
    // not cloneable
    Input(Input &other) = delete;
    // not assignable
    void operator=(const Input &) = delete;
};
