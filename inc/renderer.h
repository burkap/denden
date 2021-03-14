#ifndef RENDERER_H
#define RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
   public:
    GLFWwindow* window;
    int window_width;
    int window_height;
    const char* title;
    bool running = false;
    Renderer(int width, int height, const char* title)
        : window_width(width), window_height(height), title(title) {}
    void init();

    void fill(float r, float g, float b, float a = 1.0f);
    void render();
};

#endif