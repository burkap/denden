#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <renderer.h>

#include <cstdio>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void Renderer::init() {
    running = true;
    // Window and OpenGL context creation
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window =
        glfwCreateWindow(window_width, window_height, title, nullptr, nullptr);
    if (window == nullptr) {
        printf("Failed to create a window\n");
        glfwTerminate();
        running = false;
    }

    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // glew initiation
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Failed to initialize GLEW ERROR:%s\n", glewGetErrorString(err));
        running = false;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // imgui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");  // glsl version
}

void Renderer::fill(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}
