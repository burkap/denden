#ifndef SCENE_H
#define SCENE_H
#include <components/camera.h>
#include <cubemap.h>
#include <debugdrawer.h>
#include <gameobject.h>
#include <lightobject.h>
#include <physics.h>
#include <shadermanager.h>

#include <memory>
class Scene {
   public:
    std::shared_ptr<Shader> shader = ShaderManager::the()->get_default_shader();
    std::shared_ptr<Shader> light_shader = ShaderManager::the()->get_light_shader();
    std::shared_ptr<Shader> skybox_shader = ShaderManager::the()->get_skybox_shader();
    std::shared_ptr<Shader> debug_shader = ShaderManager::the()->get_debug_shader();

    std::shared_ptr<CubeMap> current_cubemap;
    std::vector<std::shared_ptr<GameObject>> gameobjects;
    std::vector<std::shared_ptr<LightObject>> lightobjects;
    std::shared_ptr<Camera> active_camera;
    Scene();
    std::shared_ptr<GameObject> create_gameobject(std::string);
    template <typename T>
    std::shared_ptr<T> create_lightobject(std::string);
    void set_active_camera(std::shared_ptr<Camera> camera);
    void update_all(float t);
    void step(float t);
    void render_gameobjects();
    void render_lightobjects();
    void apply_lights();
    void render_cubemap();
    void render_debug();
    void render_scene();
    void set_current_cubemap(std::shared_ptr<CubeMap> cm);
};

#endif  // SCENE_H
