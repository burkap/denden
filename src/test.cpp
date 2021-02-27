#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.h>
#include <shader.h>
#include <stddef.h> /* offsetof */
#include <transform.h>

#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    Vertex(glm::vec3 p, glm::vec3 c) : pos(p), color(c) {}
};

class Renderer {
   public:
    GLFWwindow* window;
    int window_width;
    int window_height;
    const char* title;
    bool running = false;
    Renderer(int width, int height, const char* title)
        : window_width(width), window_height(height), title(title) {}
    void init() {
        running = true;
        // Window and OpenGL context creation
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow(window_width, window_height, title, nullptr,
                                  nullptr);
        if (window == nullptr) {
            printf("Failed to create a window\n");
            glfwTerminate();
            running = false;
        }
        glfwMakeContextCurrent(window);

        // glew initiation
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (err != GLEW_OK) {
            printf("Failed to initialize GLEW ERROR:%s\n",
                   glewGetErrorString(err));
            running = false;
        }

        glEnable(GL_DEPTH_TEST);
    }

    void fill(float r, float g, float b, float a = 1.0f) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void render() {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    void run() {}
};

int main() {
    Renderer renderer(800, 800, "Test");

    Camera camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(45.0f),
                  (float)renderer.window_width / (float)renderer.window_height,
                  1.0f, 30.0f);

    renderer.init();
    Shader shader("vertex.shader", "fragment.shader");

    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),

        Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))};

    Transform test(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
                   glm::vec3(1.0, 1.0, 1.0));
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);
    // parameters respectively:
    // --------------
    // index (location in shader)
    // array length
    // array type
    // normalize?
    // size (in bytes) of each vertex
    // offset (inside the boundaries of the vertex)
    // ---------------------
    // position (x, y, z) location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);
    // // color (r, g, b) location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(1);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),   glm::vec3(0.0f, 0.0f, 1.5f),
        glm::vec3(0.0f, 0.0f, -1.5f),  glm::vec3(1.5f, 0.0f, 0.0f),
        glm::vec3(1.5f, 0.0f, 1.5f),   glm::vec3(1.5f, 0.0f, -1.5f),
        glm::vec3(-1.5f, 0.0f, 0.0f),  glm::vec3(-1.5f, 0.0f, 1.5f),
        glm::vec3(-1.5f, 0.0f, -1.5f),
    };
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(renderer.window)) {
        // Fill background
        renderer.fill(0.3f, 0.3f, 0.2f);
        float tv = glfwGetTime();
        float sin_pos = sin(tv) / 5.0f;
        float cos_pos = cos(tv) / 5.0f;
        shader.use();
        for (int i = 0; i < 9; i++) {
            glm::vec3 cur = cubePositions[i];
            test.set_rotation(glm::vec3(glm::radians(60.0f), 0.0f, 0.0f));
            test.set_scale(glm::vec3(0.3f, 0.3f, 0.3f));
            test.set_position(glm::vec3(cur.x, cur.y, cur.z + 0.0f));

            const float radius = 5 + sin_pos * 10;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;

            camera.set_pos(glm::vec3(camX, 0.0, camZ));
            glm::mat4 model = test.get_model_matrix();
            glm::mat4 view = camera.get_view_matrix();
            glm::mat4 projection = camera.get_projection_matrix();

            shader.set_mat4f("model", model);
            shader.set_mat4f("view", view);
            shader.set_mat4f("projection", projection);

            // shader.set_vec3f("test", cos_pos, sin_pos, 0.0f);
            glBindVertexArray(VAO);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        renderer.render();
    }

    glfwTerminate();
    return 1;
}