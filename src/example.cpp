#include <rigidbody.h>
#include <app.h>
#include <util.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos){}

class ExampleGame : public App{
    public:
    ExampleGame(int width, int height, std::string title) : App(width, height, title){

    }

    // This is called ONLY once just before the App::run();
    void scene_setup() override{
        std::cout << "test";
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


        Model* teapot_model = new Model(get_exe_path() + std::string("/env/p_cube.obj"));

        Model* scene_model = new Model(get_exe_path() + std::string("/env/move_scene2.obj"));

        Model* light_model = new Model(get_exe_path() + std::string("/test/cube3.obj"));
        std::shared_ptr<GameObject> teapot_object =
            scene->create_gameobject("teapot");
        teapot_object->add_component<Model>(teapot_model);
        teapot_object->get_component<Transform>()->set_position(
            glm::vec3(0.0, 5, 0.0));
        teapot_object->add_component<CollisionShape>(new MeshShape(*teapot_model));
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
        scene_object->add_component<CollisionShape>(new MeshShape(*scene_model));
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
    }
};


int main() {
    ExampleGame app(1600, 900, "Test");
    return app.run();
}
