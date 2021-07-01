#pragma once
#include <renderer.h>
#include <scene.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <globals.h>
#include <transform.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

class App{
protected:
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Scene> scene;
    bool running = true;

public:
    App(int width, int height, std::string title);
    bool run();

    virtual void scene_setup();
};
