#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.h>
#include <gameobject.h>
#include <model.h>
#include <renderer.h>
#include <shader.h>
#include <stddef.h> /* offsetof */
#include <texture.h>
#include <transform.h>
#include <util.h>

#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
#include <vector>
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static int last_x, last_y;
    last_x = xpos;
    last_y = ypos;
}

int main() {
    Renderer renderer(800, 800, "Test");

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                  glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(60.0f),
                  (float)renderer.window_width / (float)renderer.window_height,
                  0.1f, 30.0f);

    renderer.init();
    Shader shader("vertex.shader", "fragment.shader");
    Shader light_shader("light_vertex.shader", "light_fragment.shader");

    Model teapot_model;
    teapot_model.load_model(get_exe_path() + std::string("/env/monke.obj"));
    
    Model scene_model;
    scene_model.load_model(get_exe_path() + std::string("/env/scene.obj"));

    Model light_model;
    light_model.load_model(get_exe_path() + std::string("/test/cube3.obj"));

    Transform teapot_transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
                               glm::vec3(1.0, 1.0, 1.0));

    Transform scene_transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
                               glm::vec3(1.0, 1.0, 1.0));

    Transform light_transform(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0),
                              glm::vec3(1, 1, 1));

    GameObject teapot_object(teapot_transform, teapot_model);

    GameObject light_object(light_transform, light_model);

    GameObject scene_object(scene_transform, scene_model);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(renderer.window)) {
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            if (glfwGetKey(renderer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(renderer.window, true);

            if (glfwGetKey(renderer.window, GLFW_KEY_W) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(0.0, 0.0, -1.f * deltaTime * 2));
            if (glfwGetKey(renderer.window, GLFW_KEY_S) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(0.0, 0.0, 1.f * deltaTime * 2));
            if (glfwGetKey(renderer.window, GLFW_KEY_D) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(1.f * deltaTime * 2, 0.0, 0.0));
            if (glfwGetKey(renderer.window, GLFW_KEY_A) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(-1.f * deltaTime * 2, 0.0, 0.0));
            if (glfwGetKey(renderer.window, GLFW_KEY_E) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(0.0, 1.f * deltaTime * 2, 0.0));
            if (glfwGetKey(renderer.window, GLFW_KEY_C) == GLFW_PRESS)
                camera.set_pos(camera.get_pos() +
                               glm::vec3(0.0, -1.f * deltaTime * 2, 0.0));
        }

        // Fill background
        renderer.fill(0.3f, 0.3f, 0.2f);
        float tv = glfwGetTime();
        float sin_pos = sin(tv);

        shader.use();

        light_object.transform.set_position(
            glm::vec3(sin_pos * 1, 0.2, cos(tv) * 1));

        light_object.transform.set_scale(glm::vec3(0.03f, 0.03f, 0.03f));

        light_object.transform.set_rotation(glm::vec3(
            glm::radians(sin_pos * 90.0), glm::radians(cos(tv) * 90.0), 0.0f));

        teapot_object.transform.set_scale(glm::vec3(0.3f, 0.3f, 0.3f));
        teapot_object.transform.set_position(glm::vec3(0.0f, 0.0f, 0.0f));
        teapot_object.transform.set_rotation(
            glm::vec3(glm::radians(0.0), glm::radians(sin_pos*90.0), 0.0f));

        glm::mat4 model = teapot_object.transform.get_model_matrix();
        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 projection = camera.get_projection_matrix();

        shader.set_vec3f("ourColor", 1.0, 1.0, 1.0);
        shader.set_vec3f("lightColor", 1.0, 1.0, 1.0);
        shader.set_vec3f("lightPos", light_object.transform.get_position().x,
                         light_object.transform.get_position().y,
                         light_object.transform.get_position().z);

        glm::vec3 view_pos = camera.get_pos();
        shader.set_vec3f("viewPos", view_pos.x, view_pos.y, view_pos.z);
        shader.set_mat4f("model", model);
        shader.set_mat4f("view", view);
        shader.set_mat4f("projection", projection);

        teapot_object.draw(shader);
        
        scene_object.transform.set_position(glm::vec3(0.0, -1.0, -1.0));
        scene_object.transform.set_scale(glm::vec3(0.4, 0.4, 0.4));
        model = scene_object.transform.get_model_matrix();
        shader.set_mat4f("model", model);
        scene_object.draw(shader);

        light_shader.use();

        model = light_object.transform.get_model_matrix();
        light_shader.set_vec3f("ourColor", 1.0, 1.0, 1.0);
        light_shader.set_mat4f("model", model);
        light_shader.set_mat4f("view", view);
        light_shader.set_mat4f("projection", projection);

        light_object.draw(light_shader);
        renderer.render();
    }

    glfwTerminate();
    return 1;
}