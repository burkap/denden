#include <GLFW/glfw3.h>
#include <clock.h>

Clock* Clock::instance = nullptr;

double Clock::last_time = 0;
double Clock::delta_time = 0;

Clock *Clock::the()
{
    if(instance == nullptr){
        instance = new Clock();
    }
    return instance;
}

Clock::Clock()
{
    update();
}

Clock::~Clock()
{

}

double Clock::now()
{
    return last_time;
}

double Clock::dt()
{
    return delta_time;
}

void Clock::update()
{
    double current = glfwGetTime();
    delta_time = current - last_time;
    last_time = current;
}
