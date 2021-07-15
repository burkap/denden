#pragma once
#include <renderer.h>
#include <keycodes.h>

class Input
{
    static Input* instance;
    static GLFWwindow* window;
    static double last_pos_x;
    static double last_pos_y;
    static int screen_width;
    static int screen_height;
public:
    Input();
    static bool is_key_down(int KEYCODE);
    static void set_window(GLFWwindow* w);
    static double get_mouse_diff_x();
    static double get_mouse_diff_y();

    static void update_mouse_positions();
    static Input* the();
    // not cloneable
    Input(Input &other) = delete;
    // not assignable
    void operator=(const Input &) = delete;
};
