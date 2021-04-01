#ifndef SCENE_H
#define SCENE_H
#include <camera.h>
#include <memory>
#include <gameobject.h>
#include <lightobject.h>
#include <cubemap.h>

class Scene
{
public:
    std::shared_ptr<CubeMap> current_cubemap;
    std::vector<std::shared_ptr<GameObject>> gameobjects;
    std::vector<std::shared_ptr<LightObject>> lightobjects;
    std::shared_ptr<Camera> active_camera;
    Scene();
    std::shared_ptr<GameObject> create_gameobject(std::string);
    template <typename T> std::shared_ptr<T> create_lightobject(std::string);
    void set_active_camera(Camera &camera);
    void draw(Shader &shader, Shader &light_shader, Shader &skybox_shader);
    void set_current_cubemap(CubeMap &cm);
};

#endif // SCENE_H
