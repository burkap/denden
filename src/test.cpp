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
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <component.h>
#include <memory>
#include <scene.h>
#include <globals.h>

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
    teapot_model.load_model(get_exe_path() + std::string("/env/bunny.obj"));

    Model scene_model;
    scene_model.load_model(get_exe_path() + std::string("/env/new_scene2.obj"));

    Model light_model;
    light_model.load_model(get_exe_path() + std::string("/test/cube3.obj"));
    Scene scene;
    scene.set_active_camera(camera);
    std::shared_ptr<GameObject> teapot_object = scene.create_gameobject("teapot");
    teapot_object->add_component<Transform>();
    teapot_object->add_component<Model>(teapot_model);
    teapot_object->add_component<TestComponent>();

    std::shared_ptr<GameObject> scene_object = scene.create_gameobject("plane");
    scene_object->add_component<Transform>();
    scene_object->add_component<Model>(scene_model);
    scene_object->get_component<Transform>()->set_position(glm::vec3(-1.0, -3, 0.0));

    std::shared_ptr<PointLight> light_object = scene.create_lightobject<PointLight>("light1");
    light_object->add_component<Model>(light_model);
    light_object->add_component<Transform>();

    std::shared_ptr<PointLight> light2_object = scene.create_lightobject<PointLight>("light2");
    light2_object->add_component<Model>(light_model);
    light2_object->add_component<Transform>();

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool light_move = true;
    while (!glfwWindowShouldClose(renderer.window)) {
        {
            if (Globals::render_wireframe)
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
        if (light_move)
            light_object->get_component<Transform>()->set_position(
                glm::vec3(sin_pos * 1, light2_object->get_component<Transform>()->m_position.y, cos(tv) * 1));
        if (light_move)
            light2_object->get_component<Transform>()->set_position(
                glm::vec3(cos(tv) * 1, light2_object->get_component<Transform>()->m_position.y, sin_pos * 1));

        light_object->get_component<Transform>()->set_scale(glm::vec3(0.03f, 0.03f, 0.03f));
        light_object->get_component<Transform>()->set_rotation(glm::vec3(
            glm::radians(sin_pos * 90.0), glm::radians(cos(tv) * 90.0), 0.0f));

        light2_object->get_component<Transform>()->set_scale(glm::vec3(0.03f, 0.03f, 0.03f));
        light2_object->get_component<Transform>()->set_rotation(glm::vec3(
            glm::radians(sin_pos * 90.0), glm::radians(cos(tv) * 90.0), 0.0f));

        scene.draw(shader, light_shader);

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static int counter = 0;
            ImGui::Begin("Test Window");

            ImGui::Text("Test text");
            ImGui::Checkbox("Light move", &light_move);
            ImGui::Checkbox("Draw wireframe", &Globals::render_wireframe);
            ImGui::Checkbox("Enable custom lighting", &Globals::enable_custom_lighting);
            ImGui::Checkbox("Enable Blinn lighting", &Globals::enable_blinn);

            ImGui::Text("Test text");

            if (ImGui::Button("Button")) counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();

            ImGui::Begin("Scene");

            ImGui::Text("Scene");
            if (ImGui::CollapsingHeader("GameObjects"))
            {
                ImGui::Indent();
                for(std::shared_ptr<GameObject> &go : scene.gameobjects){
                    if(ImGui::TreeNode((go->name + " ID: " + std::to_string(go->id)).c_str())){
                        int i = 0;
                        for(auto &c : go->components){
                            ImGui::PushID(i);
                            ImGui::BulletText(c.first.name());
                            if(c.first == typeid(Transform))
                            {
                                std::shared_ptr<Transform> tf = std::dynamic_pointer_cast<Transform>(c.second);
                                glm::vec3 tf_pos = tf->get_position();
                                glm::vec3 tf_rot = tf->get_rotation();
                                glm::vec3 tf_scale = tf->get_scale();
                                ImGui::SliderFloat3("Pos", glm::value_ptr(tf_pos), -1, 1);
                                tf->set_position(tf_pos);
                                ImGui::SliderFloat3("Rot", glm::value_ptr(tf_rot), -1, 1);
                                tf->set_rotation(tf_rot);
                                ImGui::SliderFloat3("Scale", glm::value_ptr(tf_scale), 0, 1);
                                tf->set_scale(tf_scale);
                            }
                            ImGui::PopID();
                            i++;
                        }
                    ImGui::TreePop();
                    }
                }
                ImGui::Unindent();
            }

            if (ImGui::CollapsingHeader("LightObjects"))
            {
                ImGui::Indent();
                for(std::shared_ptr<LightObject> &lo : scene.lightobjects){
                    if(ImGui::TreeNode((lo->name+ " ID: " + std::to_string(lo->id)).c_str())){
                        int i = 0;
                        float temp[3];
                        temp[0] = lo->color.x;
                        temp[1] = lo->color.y;
                        temp[2] = lo->color.z;
                        ImGui::ColorEdit3("Light", temp);
                        lo->color.x = temp[0];
                        lo->color.y = temp[1];
                        lo->color.z = temp[2];
                        for(auto &c : lo->components){
                            ImGui::PushID(i);
                            ImGui::Text(c.first.name()+1);
                            if(c.first == typeid(Transform))
                            {
                                std::shared_ptr<Transform> tf = std::dynamic_pointer_cast<Transform>(c.second);
                                glm::vec3 tf_pos = tf->get_position();
                                glm::vec3 tf_rot = tf->get_rotation();
                                glm::vec3 tf_scale = tf->get_scale();
                                ImGui::SliderFloat3("Pos", glm::value_ptr(tf_pos), -1, 1);
                                tf->set_position(tf_pos);
                                ImGui::SliderFloat3("Rot", glm::value_ptr(tf_rot), -1, 1);
                                tf->set_rotation(tf_rot);
                                ImGui::SliderFloat3("Scale", glm::value_ptr(tf_scale), 0, 1);
                                tf->set_scale(tf_scale);
                            }
                            ImGui::PopID();
                            i++;
                        }
                    ImGui::TreePop();
                    }
                }
                ImGui::Unindent();
            }

            ImGui::End();
        }
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(renderer.window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(renderer.window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 1;
}
