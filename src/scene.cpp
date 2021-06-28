#include <globals.h>
#include <model.h>
#include <rigidbody.h>
#include <scene.h>
#include <transform.h>

#include <shadermanager.h>
#include <glm/gtc/quaternion.hpp>

Scene::Scene() {
}

std::shared_ptr<GameObject> Scene::create_gameobject(std::string name) {
    std::shared_ptr<GameObject> new_object = std::make_shared<GameObject>(name);
    new_object->add_component<Transform>();
    gameobjects.push_back(new_object);
    return new_object;
}

template <typename T>
std::shared_ptr<T> Scene::create_lightobject(std::string name) {
    std::shared_ptr<T> new_object = std::make_shared<T>(name);
    lightobjects.push_back(new_object);
    return new_object;
}
template std::shared_ptr<PointLight> Scene::create_lightobject<PointLight>(
    std::string name);

void Scene::set_active_camera(std::shared_ptr<Camera> camera) {
    active_camera = camera;
}

void Scene::update_all(float t){
    for (std::shared_ptr<GameObject> &g : gameobjects){
        for(auto &a : g->components){
            std::shared_ptr<Component> c = a.second;
            c->update(t);
        }
    }
}

void Scene::step(float t) {
    if (!Globals::simulate_steps) return;
    Physics::the()->step(t);

    for (std::shared_ptr<GameObject> &g :
         gameobjects) {  // loop through all gameobjects
        std::shared_ptr<RigidBody> rb = g->get_component<RigidBody>();
        if (rb != nullptr)  // that have a RigidBody component
        {
            btTransform t;
            rb->get_rigidbody()->getMotionState()->getWorldTransform(t);
            btVector3 pos = t.getOrigin();
            btQuaternion rot = t.getRotation();
            glm::quat q(rot.getW(), rot.getX(), rot.getY(), rot.getZ());

            std::shared_ptr<Transform> g_t = g->get_component<Transform>();
            g_t->set_position(glm::vec3(pos.getX(), pos.getY(), pos.getZ()));
            if (Globals::rotate_collision) g_t->m_quaternion = q;
        }
    }
}
void Scene::draw() {
    glm::mat4 view_matrix = active_camera->get_view_matrix();
    glm::mat4 projection_matrix = active_camera->get_projection_matrix();

    std::shared_ptr<Shader> shader = ShaderManager::the()->get_default_shader();
    std::shared_ptr<Shader> light_shader = ShaderManager::the()->get_light_shader();
    std::shared_ptr<Shader> skybox_shader = ShaderManager::the()->get_skybox_shader();
    std::shared_ptr<Shader> debug_shader = ShaderManager::the()->get_debug_shader();
    light_shader->use();
    light_shader->set_mat4f("view", view_matrix);
    light_shader->set_mat4f("projection", projection_matrix);
    for (std::shared_ptr<LightObject> &lo : lightobjects) {
        std::shared_ptr<Model> model = lo->get_component<Model>();
        if (model == nullptr) continue;

        std::shared_ptr<Transform> transform = lo->get_component<Transform>();
        if (transform == nullptr) continue;

        glm::vec3 light_color = lo->color;
        lo->set_diffuse(
            glm::vec3(light_color.x / 2, light_color.y / 2, light_color.z / 2));
        lo->set_specular(
            glm::vec3(light_color.x, light_color.y, light_color.z));
        lo->set_ambient(
            glm::vec3(light_color.x / 5, light_color.y / 5, light_color.z / 5));

        light_shader->set_vec3f("ourColor", light_color.x, light_color.y,
                               light_color.z);
        light_shader->set_mat4f("model", transform->get_model_matrix());
        model->draw(light_shader.get());
    }

    shader->use();
    for (std::shared_ptr<LightObject> &lo : lightobjects) {
        lo->apply(shader);
    }
    glm::vec3 view_pos = active_camera->get_pos();
    view_pos = glm::normalize(glm::vec3(view_matrix * glm::vec4(view_pos, 0.)));
    shader->set_vec3f("viewPos", view_pos.x, view_pos.y, view_pos.z);
    shader->set_mat4f("view", view_matrix);
    shader->set_mat4f("projection", projection_matrix);
    for (std::shared_ptr<GameObject> &go : gameobjects) {
        std::shared_ptr<Model> model = go->get_component<Model>();
        if (model == nullptr) continue;

        std::shared_ptr<Transform> transform = go->get_component<Transform>();
        if (transform == nullptr) continue;

        shader->set_mat4f("model", transform->get_model_matrix());
        shader->set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader->set_float("material.shininess", 1.0f);
        shader->set_bool("enable_custom_spec", Globals::enable_custom_lighting);
        shader->set_bool("enable_blinn", Globals::enable_blinn);
        model->draw(shader.get());
    }

    glDepthFunc(GL_LEQUAL);
    skybox_shader->use();
    glm::mat4 no_trans_view_matrix = glm::mat4(
        glm::mat3(view_matrix));  // remove translation from the view matrix
    skybox_shader->set_mat4f("view", no_trans_view_matrix);
    skybox_shader->set_mat4f("projection", projection_matrix);

    glBindVertexArray(current_cubemap->get_vao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, current_cubemap->get_id());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

    Physics::the()->get_debug_drawer()->set_shader(debug_shader);
    Physics::the()->get_debug_drawer()->set_view(active_camera->get_view_matrix());
    Physics::the()->get_debug_drawer()->set_projection(active_camera->get_projection_matrix());

    Physics::the()->get_world()->debugDrawWorld();
    Physics::the()->get_debug_drawer()->drawAll();
}

void Scene::set_current_cubemap(CubeMap &cm) {
    current_cubemap = std::shared_ptr<CubeMap>(&cm);
}
