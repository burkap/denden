#include <input.h>

Input* Input::instance = nullptr;
GLFWwindow* Input::window = nullptr;
double Input::last_pos_x = 0;
double Input::last_pos_y = 0;
int Input::screen_width = 0;
int Input::screen_height = 0;

Input::Input()
{

}

bool Input::is_key_down(int KEYCODE)
{
    return (glfwGetKey(window, KEYCODE) == GLFW_PRESS);
}

void Input::set_window(GLFWwindow* w)
{
    window = w;
    glfwGetFramebufferSize(window, &screen_width, &screen_height);
}

double Input::get_mouse_diff_x()
{
    double posx, posy;
    glfwGetCursorPos(window, &posx, &posy);
    return (posx - last_pos_x)/screen_width;
}

double Input::get_mouse_diff_y()
{
    double posx, posy;
    glfwGetCursorPos(window, &posx, &posy);
    return (posy - last_pos_y)/screen_height;
}

void Input::update_mouse_positions()
{
    glfwGetCursorPos(window, &last_pos_x, &last_pos_y);
}


Input *Input::the()
{
    if(instance == nullptr){
            instance = new Input();
    }
    return instance;
}
