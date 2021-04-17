#include <globals.h>
#include <model.h>
#include <rigidbody.h>
#include <scene.h>
#include <transform.h>

#include <glm/gtc/quaternion.hpp>

Scene::Scene() {
    physics_handler.init();

    debug_drawer = new DebugDrawer();
    debug_drawer->setDebugMode(
        ((Globals::debug_draw_AABB) ? btIDebugDraw::DBG_DrawAabb : 0) +
        ((Globals::debug_draw_wireframe) ? btIDebugDraw::DBG_DrawWireframe
                                         : 0));
    physics_handler.set_debug_drawer(debug_drawer);
}

std::shared_ptr<GameObject> Scene::create_gameobject(std::string name) {
    std::shared_ptr<GameObject> new_object = std::make_shared<GameObject>(name);
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

void Scene::set_active_camera(Camera &camera) {
    active_camera = std::shared_ptr<Camera>(&camera);
}

void Scene::step(float t) {
    if (!Globals::simulate_steps) return;
    physics_handler.step(t);

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
void Scene::draw(Shader &shader, Shader &light_shader, Shader &skybox_shader,
                 Shader &debug_shader) {
    glm::mat4 view_matrix = active_camera->get_view_matrix();
    glm::mat4 projection_matrix = active_camera->get_projection_matrix();

    light_shader.use();
    light_shader.set_mat4f("view", view_matrix);
    light_shader.set_mat4f("projection", projection_matrix);
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

        light_shader.set_vec3f("ourColor", light_color.x, light_color.y,
                               light_color.z);
        light_shader.set_mat4f("model", transform->get_model_matrix());
        model->draw(light_shader);
    }

    shader.use();
    for (std::shared_ptr<LightObject> &lo : lightobjects) {
        lo->apply(shader);
    }
    glm::vec3 view_pos = active_camera->get_pos();
    shader.set_vec3f("viewPos", view_pos.x, view_pos.y, view_pos.z);
    shader.set_mat4f("view", view_matrix);
    shader.set_mat4f("projection", projection_matrix);
    for (std::shared_ptr<GameObject> &go : gameobjects) {
        std::shared_ptr<Model> model = go->get_component<Model>();
        if (model == nullptr) continue;

        std::shared_ptr<Transform> transform = go->get_component<Transform>();
        if (transform == nullptr) continue;

        shader.set_mat4f("model", transform->get_model_matrix());
        shader.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader.set_float("material.shininess", 1.0f);
        shader.set_bool("enable_custom_spec", Globals::enable_custom_lighting);
        shader.set_bool("enable_blinn", Globals::enable_blinn);
        model->draw(shader);
    }

    glDepthFunc(GL_LEQUAL);
    skybox_shader.use();
    glm::mat4 no_trans_view_matrix = glm::mat4(
        glm::mat3(view_matrix));  // remove translation from the view matrix
    skybox_shader.set_mat4f("view", no_trans_view_matrix);
    skybox_shader.set_mat4f("projection", projection_matrix);

    glBindVertexArray(current_cubemap->get_vao());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, current_cubemap->get_id());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);

    debug_drawer->set_shader(&debug_shader);
    debug_drawer->set_view(active_camera->get_view_matrix());
    debug_drawer->set_projection(active_camera->get_projection_matrix());

    physics_handler.get_world()->debugDrawWorld();
    debug_drawer->drawAll();
}

void Scene::set_current_cubemap(CubeMap &cm) {
    current_cubemap = std::shared_ptr<CubeMap>(&cm);
}
