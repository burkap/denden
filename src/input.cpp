#include <input.h>

Input* Input::instance = nullptr;
GLFWwindow* Input::window = nullptr;

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
}

Input *Input::the()
{
    if(instance == nullptr){
            instance = new Input();
    }
    return instance;
}
