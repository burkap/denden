#pragma once
#include <app.h>
#include <model.h>
#include <transform.h>
#include <collisionshape.h>

#include <rigidbody.h>
#include <lightobject.h>
#include <util.h>

App::App(){
    renderer = std::make_shared<Renderer>(1600, 900, "Test");
    renderer->init();

    scene = std::make_shared<Scene>();
    std::shared_ptr<GameObject> camera_object = scene->create_gameobject("Main Camera");
    camera_object->add_component<Camera>(new Camera(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                                                           glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(75.0f),
                                                           (float)renderer->window_width / (float)renderer->window_height,
                                                           0.1f, 120.0f));
    scene->set_active_camera(camera_object->get_component<Camera>());
    std::vector<std::string> faces = {"skybox/right.jpg", "skybox/left.jpg",
                                      "skybox/top.jpg",   "skybox/bottom.jpg",
                                      "skybox/front.jpg", "skybox/back.jpg"};

    scene->set_current_cubemap(std::make_shared<CubeMap>(faces));


    Model teapot_model;
    teapot_model.load_model(get_exe_path() + std::string("/env/p_cube.obj"));

    Model scene_model;
    scene_model.load_model(get_exe_path() + std::string("/env/move_scene2.obj"));

    Model light_model;
    light_model.load_model(get_exe_path() + std::string("/test/cube3.obj"));
    std::shared_ptr<GameObject> teapot_object =
        scene->create_gameobject("teapot");
    teapot_object->add_component<Model>(teapot_model);
    teapot_object->get_component<Transform>()->set_position(
        glm::vec3(0.0, 5, 0.0));
    teapot_object->add_component<CollisionShape>(new MeshShape(teapot_model));
    teapot_object->add_component<RigidBody>(new RigidBody(0.1));

    std::shared_ptr<GameObject> teapot_object2 =
        scene->create_gameobject("teapot2");
    teapot_object2->add_component<Model>(teapot_model);
    teapot_object2->get_component<Transform>()->set_position(
        glm::vec3(1.3, 9, 0.0));
    teapot_object2->add_component<CollisionShape>(new BoxShape(1, 1, 1));
    teapot_object2->add_component<RigidBody>(new RigidBody(0.1));

    for (int i = 0; i < 5; i++) {
        std::shared_ptr<GameObject> aa =
            scene->create_gameobject("cube_" + std::to_string(i));
        aa->add_component<Model>(teapot_model);
        aa->get_component<Transform>()->set_position(
            glm::vec3(1.3 + i % 5, 9 + i, i % 5));
        aa->add_component<CollisionShape>(new BoxShape(1, 1, 1));
        aa->add_component<RigidBody>(new RigidBody(0.1));
    }

    std::shared_ptr<GameObject> cube = scene->create_gameobject("cube");
    cube->add_component<Model>(teapot_model);
    cube->get_component<Transform>()->set_position(glm::vec3(1, 15, 0.0));

    std::shared_ptr<GameObject> scene_object = scene->create_gameobject("plane");
    scene_object->add_component<Model>(scene_model);
    scene_object->get_component<Transform>()->set_position(
        glm::vec3(0.0, -5, 0.0));
    scene_object->get_component<Transform>()->set_scale(glm::vec3(1));
    scene_object->add_component<CollisionShape>(new MeshShape(scene_model));
    scene_object->add_component<RigidBody>();

    std::shared_ptr<PointLight> light_object =
        scene->create_lightobject<PointLight>("light1");
    light_object->add_component<Model>(light_model);
    light_object->add_component<Transform>();

    std::shared_ptr<PointLight> light2_object =
        scene->create_lightobject<PointLight>("light2");
    light2_object->add_component<Model>(light_model);
    light2_object->add_component<Transform>();


    std::shared_ptr<DirectionalLight> directional_light =
            scene->create_lightobject<DirectionalLight>("Dir_light");
    directional_light->add_component<Model>(light_model);
    directional_light->add_component<Transform>();
    directional_light->set_direction(glm::vec3(0, 0.3, 1));
    run();
}

void App::run(){
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
