#ifndef SCENE_H
#define SCENE_H
#include <camera.h>
#include <cubemap.h>
#include <debugdrawer.h>
#include <gameobject.h>
#include <lightobject.h>
#include <physics.h>

#include <memory>
class Scene {
   public:
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
    void draw();
    void set_current_cubemap(CubeMap &cm);
};

#endif  // SCENE_H
