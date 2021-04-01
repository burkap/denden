#include <scene.h>
#include <globals.h>

Scene::Scene()
{

}

std::shared_ptr<GameObject> Scene::create_gameobject(std::string name)
{
    std::shared_ptr<GameObject> new_object = std::make_shared<GameObject>(name);
    gameobjects.push_back(new_object);
    return new_object;
}

template<typename T>
std::shared_ptr<T> Scene::create_lightobject(std::string name)
{
    std::shared_ptr<T> new_object = std::make_shared<T>(name);
    lightobjects.push_back(new_object);
    return new_object;
}
template std::shared_ptr<PointLight> Scene::create_lightobject<PointLight>(std::string name);

void Scene::set_active_camera(Camera &camera)
{
    active_camera = std::shared_ptr<Camera>(&camera);
}

void Scene::draw(Shader &shader, Shader &light_shader)
{
    glm::mat4 view_matrix = active_camera->get_view_matrix();
    glm::mat4 projection_matrix = active_camera->get_projection_matrix();

    light_shader.use();
    light_shader.set_mat4f("view", view_matrix);
    light_shader.set_mat4f("projection", projection_matrix);
    for(std::shared_ptr<LightObject> &lo : lightobjects){
        std::shared_ptr<Model> model = lo->get_component<Model>();
        if(model == nullptr) continue;

        std::shared_ptr<Transform> transform = lo->get_component<Transform>();
        if(transform == nullptr) continue;

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
    for(std::shared_ptr<LightObject> &lo : lightobjects)
    {
        lo->apply(shader);
    }
    glm::vec3 view_pos = active_camera->get_pos();
    shader.set_vec3f("viewPos", view_pos.x, view_pos.y, view_pos.z);
    shader.set_mat4f("view", view_matrix);
    shader.set_mat4f("projection", projection_matrix);
    for (std::shared_ptr<GameObject> &go : gameobjects){
        std::shared_ptr<Model> model = go->get_component<Model>();
        if(model == nullptr) continue;

        std::shared_ptr<Transform> transform = go->get_component<Transform>();
        if(transform == nullptr) continue;

        shader.set_mat4f("model", transform->get_model_matrix());
        shader.set_vec3f("material.specular", 0.5f, 0.5f, 0.5f);
        shader.set_float("material.shininess", 1.0f);
        shader.set_bool("enable_custom_spec", Globals::enable_custom_lighting);
        shader.set_bool("enable_blinn", Globals::enable_blinn);
        model->draw(shader);
    }
}
