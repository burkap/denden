#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.h>
#include <gameobject.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <lightobject.h>
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
#include <component.h>
#include <memory>

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
    teapot_model.load_model(get_exe_path() + std::string("/env/new_cube.obj"));

    Model scene_model;
    scene_model.load_model(get_exe_path() + std::string("/env/new_scene.obj"));

    Model light_model;
    light_model.load_model(get_exe_path() + std::string("/test/cube3.obj"));

    GameObject teapot_object;
    teapot_object.add_component<Transform>();
    teapot_object.add_component<Model>(teapot_model);

    teapot_object.add_component<TestComponent>();
    std::shared_ptr<Component> keke = teapot_object.get_component<TestComponent>();
    PointLight light_object;
    light_object.add_component<Model>(light_model);
    light_object.add_component<Transform>();
    PointLight light2_object;
    light2_object.add_component<Model>(light_model);
    light2_object.add_component<Transform>();

    std::vector<PointLight> point_lights;
    point_lights.push_back(light_object);
    point_lights.push_back(light2_object);

    GameObject scene_object;
    scene_object.add_component<Transform>();
    scene_object.add_component<Model>(scene_model);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    ImVec4 light_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImVec4 light2_color = ImVec4(0.45f, 1.0f, 0.60f, 1.00f);
    bool light_move = true;
    bool enable_custom = false;
    bool wireframe = false;
    while (!glfwWindowShouldClose(renderer.window)) {
        {
            if (wireframe)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

        if (light_move)
            light_object.get_component<Transform>()->set_position(
                glm::vec3(sin_pos * 1, 0.2, cos(tv) * 1));
        if (light_move)
            light2_object.get_component<Transform>()->set_position(
                glm::vec3(cos(tv) * 1, 0.5, sin_pos * 1));

        light_object.get_component<Transform>()->set_scale(glm::vec3(0.03f, 0.03f, 0.03f));
        light_object.get_component<Transform>()->set_rotation(glm::vec3(
            glm::radians(sin_pos * 90.0), glm::radians(cos(tv) * 90.0), 0.0f));

        light2_object.get_component<Transform>()->set_scale(glm::vec3(0.03f, 0.03f, 0.03f));
        light2_object.get_component<Transform>()->set_rotation(glm::vec3(
            glm::radians(sin_pos * 90.0), glm::radians(cos(tv) * 90.0), 0.0f));

        teapot_object.get_component<Transform>()->set_scale(glm::vec3(0.3f, 0.3f, 0.3f));
        teapot_object.get_component<Transform>()->set_position(glm::vec3(0.0f, 0.3f, 0.0f));
        teapot_object.get_component<Transform>()->set_rotation(
            glm::vec3(glm::radians(0.0), glm::radians(90.0), 0.0f));

        glm::mat4 model = teapot_object.get_component<Transform>()->get_model_matrix();
        glm::mat4 view = camera.get_view_matrix();
        glm::mat4 projection = camera.get_projection_matrix();

        light_object.set_diffuse(
            glm::vec3(light_color.x / 2, light_color.y / 2, light_color.z / 2));
        light_object.set_specular(
            glm::vec3(light_color.x, light_color.y, light_color.z));
        light_object.set_ambient(
            glm::vec3(light_color.x / 5, light_color.y / 5, light_color.z / 5));

        light2_object.set_diffuse(glm::vec3(
            light2_color.x / 2, light2_color.y / 2, light2_color.z / 2));
        light2_object.set_specular(
            glm::vec3(light2_color.x, light2_color.y, light2_color.z));
        light2_object.set_ambient(glm::vec3(
            light2_color.x / 5, light2_color.y / 5, light2_color.z / 5));

        // for( PointLight &light : point_lights ){
        //     light.apply(shader);
        // }

        light_object.apply(shader);
        light2_object.apply(shader);

        //        for(int i = 0; i < PointLight::count; i++) {
        //            point_lights[i].apply(shader);
        //        }

        glm::vec3 view_pos = camera.get_pos();
        shader.set_vec3f("viewPos", view_pos.x, view_pos.y, view_pos.z);
        shader.set_mat4f("model", model);
        shader.set_mat4f("view", view);
        shader.set_mat4f("projection", projection);
        shader.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader.set_float("material.shininess", 1.0f);
        shader.set_bool("enable_custom_spec", enable_custom);
        teapot_object.get_component<Model>()->draw(shader);

        scene_object.get_component<Transform>()->set_position(glm::vec3(0.0, -1.0, -1.0));
        scene_object.get_component<Transform>()->set_scale(glm::vec3(0.4, 0.4, 0.4));
        model = scene_object.get_component<Transform>()->get_model_matrix();
        shader.set_mat4f("model", model);
        shader.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader.set_float("material.shininess", 1.0f);
        shader.set_bool("enable_custom_spec", enable_custom);
        scene_object.get_component<Model>()->draw(shader);

        light_shader.use();

        model = light_object.get_component<Transform>()->get_model_matrix();
        light_shader.set_vec3f("ourColor", light_color.x, light_color.y,
                               light_color.z);
        light_shader.set_mat4f("model", model);
        light_shader.set_mat4f("view", view);
        light_shader.set_mat4f("projection", projection);

        light_object.get_component<Model>()->draw(light_shader);

        model = light2_object.get_component<Transform>()->get_model_matrix();
        light_shader.set_vec3f("ourColor", light2_color.x, light2_color.y,
                               light2_color.z);
        light_shader.set_mat4f("model", model);
        light2_object.get_component<Model>()->draw(light_shader);
        // renderer.render();

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static int counter = 0;
            ImGui::Begin("Test Window");

            ImGui::Text("Test text");
            ImGui::Checkbox("Light move", &light_move);
            ImGui::Checkbox("Draw wireframe", &wireframe);
            ImGui::Checkbox("Enable custom lighting", &enable_custom);
            ImGui::ColorEdit3("Light color", (float*)&light_color);
            ImGui::Text("Test text");
            ImGui::ColorEdit3("Light2 color", (float*)&light2_color);

            if (ImGui::Button("Button")) counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(renderer.window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(renderer.window);
    }

    glfwTerminate();
    return 1;
}
