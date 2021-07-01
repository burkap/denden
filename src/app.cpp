#pragma once
#include <app.h>
#include <model.h>
#include <transform.h>
#include <collisionshape.h>

#include <input.h>
#include <rigidbody.h>
#include <lightobject.h>
#include <util.h>

App::App(int width, int height, std::string title){
    /*
     * 1. Create renderer
     * 2. Setup Input Manager (pass the window from renderer to input manager) [GLFW specific]
     * 3. Create scene
     */
    renderer = std::make_shared<Renderer>(width, height, title.c_str());
    renderer->init();

    Input::set_window(renderer->window);
    scene = std::make_shared<Scene>();
}

bool App::run(){
    scene_setup();
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    while(running){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        //update_inputs();
        //before_frame();
        /* v
         * pollJoypad(event);
         * updatePlayerControls(event);
         * updateDynamicsSimulation(event);
         * resolveCollisions(event);
         * updateCamera(event);
         */
        renderer->fill(0.3f, 0.3f, 0.2f);
        scene->step(deltaTime);
        scene->update_all(deltaTime);
        scene->render_scene();

        glfwPollEvents();
        //after_frame();
        {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static int counter = 0;
            ImGui::Begin("Test Window");

            ImGui::Text("Test text");
            ImGui::Checkbox("Draw wireframe", &Globals::render_wireframe);
            ImGui::Checkbox("Enable custom lighting",
                            &Globals::enable_custom_lighting);
            ImGui::Checkbox("Enable Blinn lighting", &Globals::enable_blinn);
            ImGui::Checkbox("Enable physics rotation",
                            &Globals::rotate_collision);
            ImGui::Checkbox("Simulate physics", &Globals::simulate_steps);
            ImGui::Checkbox("Debug AABB", &Globals::debug_draw_AABB);
            ImGui::Checkbox("Debug Wireframe", &Globals::debug_draw_wireframe);
            Physics::the()->get_debug_drawer()->setDebugMode(
                ((Globals::debug_draw_AABB) ? btIDebugDraw::DBG_DrawAabb : 0) +
                ((Globals::debug_draw_wireframe)
                     ? btIDebugDraw::DBG_DrawWireframe
                     : 0));

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
            if (ImGui::CollapsingHeader("GameObjects")) {
                ImGui::Indent();
                for (std::shared_ptr<GameObject>& go : scene->gameobjects) {
                    if (ImGui::TreeNode(
                            (go->name + " ID: " + std::to_string(go->id))
                                .c_str())) {
                        int i = 0;
                        for (auto& c : go->components) {
                            ImGui::PushID(i);
                            ImGui::BulletText(c.first.name());
                            if (c.first == typeid(Transform)) {
                                std::shared_ptr<Transform> tf =
                                    std::dynamic_pointer_cast<Transform>(
                                        c.second);
                                glm::vec3 tf_pos = tf->get_position();
                                glm::vec3 tf_rot = tf->get_rotation();
                                glm::vec3 tf_scale = tf->get_scale();
                                ImGui::SliderFloat3(
                                    "Pos", glm::value_ptr(tf_pos), -1, 1);
                                tf->set_position(tf_pos);
                                ImGui::SliderFloat3(
                                    "Rot", glm::value_ptr(tf_rot), -10, 10);
                                tf->set_rotation(tf_rot);
                                ImGui::SliderFloat3(
                                    "Scale", glm::value_ptr(tf_scale), 0, 1);
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

            if (ImGui::CollapsingHeader("LightObjects")) {
                ImGui::Indent();
                for (std::shared_ptr<LightObject>& lo : scene->lightobjects) {
                    if (ImGui::TreeNode(
                            (lo->name + " ID: " + std::to_string(lo->id))
                                .c_str())) {
                        int i = 0;
                        float temp[3];
                        temp[0] = lo->color.x;
                        temp[1] = lo->color.y;
                        temp[2] = lo->color.z;
                        ImGui::ColorEdit3("Light", temp);
                        lo->color.x = temp[0];
                        lo->color.y = temp[1];
                        lo->color.z = temp[2];
                        for (auto& c : lo->components) {
                            ImGui::PushID(i);
                            ImGui::Text(c.first.name() + 1);
                            if (c.first == typeid(Transform)) {
                                std::shared_ptr<Transform> tf =
                                    std::dynamic_pointer_cast<Transform>(
                                        c.second);
                                glm::vec3 tf_pos = tf->get_position();
                                glm::vec3 tf_rot = tf->get_rotation();
                                glm::vec3 tf_scale = tf->get_scale();
                                ImGui::SliderFloat3(
                                    "Pos", glm::value_ptr(tf_pos), -1, 1);
                                tf->set_position(tf_pos);
                                ImGui::SliderFloat3(
                                    "Rot", glm::value_ptr(tf_rot), -1, 1);
                                tf->set_rotation(tf_rot);
                                ImGui::SliderFloat3(
                                    "Scale", glm::value_ptr(tf_scale), 0, 1);
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
        glfwGetFramebufferSize(renderer->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(renderer->window);
        }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void App::scene_setup()
{
    std::cout << "You should create a class that inherits App and overrides scene_setup();\n";
}
