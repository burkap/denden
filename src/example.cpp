#include <rigidbody.h>
#include <app.h>
#include <util.h>
#include <components/lambdascript.h>
#include <input.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos){}

class ExampleGame : public App{
    public:
    ExampleGame(int width, int height, std::string title) : App(width, height, title){

    }

    // This is called ONLY once just before the App::run();
    void scene_setup() override{
        // Create main camera
        std::shared_ptr<GameObject> camera_object = scene->create_gameobject("Main Camera");
        camera_object->add_component<Camera>(new Camera(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, -1.0f),
                                                               glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(75.0f),
                                                               (float)renderer->window_width / (float)renderer->window_height,
                                                               0.1f, 120.0f));
        scene->set_active_camera(camera_object->get_component<Camera>());

        // Create skybox
        std::vector<std::string> faces = {"skybox/right.jpg", "skybox/left.jpg",
                                          "skybox/top.jpg",   "skybox/bottom.jpg",
                                          "skybox/front.jpg", "skybox/back.jpg"};

        scene->set_current_cubemap(std::make_shared<CubeMap>(faces));


        // Load models
        Model* cube_model = new Model(get_exe_path() + std::string("/env/p_cube.obj"));

        Model* scene_model = new Model(get_exe_path() + std::string("/env/move_scene2.obj"));

        Model* light_model = new Model(get_exe_path() + std::string("/test/cube3.obj"));

        std::shared_ptr<GameObject> input_handler = scene->create_gameobject("input handler");
        std::shared_ptr<LambdaScript> lambda = input_handler->add_component<LambdaScript>(new LambdaScript());
        lambda->set_update_func([](LambdaScript* ref, float dt){
            if(Input::is_key_down(KEY_ENTER)) std::cout << "test\n";
        });

        std::shared_ptr<GameObject> teapot_object =
            scene->create_gameobject("teapot");
        teapot_object->add_component<Model>(cube_model);
        teapot_object->get_component<Transform>()->set_position(
            glm::vec3(0.0, 5, 0.0));
        teapot_object->add_component<Collider>(new BoxCollider(1, 1, 1));
        teapot_object->add_component<RigidBody>(new RigidBody(0.1));

        std::shared_ptr<GameObject> teapot_object2 =
            scene->create_gameobject("teapot2");
        teapot_object2->add_component<Model>(cube_model);
        teapot_object2->get_component<Transform>()->set_position(
            glm::vec3(1.3, 9, 0.0));
        teapot_object2->add_component<Collider>(new BoxCollider(1, 1, 1));
        teapot_object2->add_component<RigidBody>(new RigidBody(0.1));

        int cubeno = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 5; k++) {
                    std::shared_ptr<GameObject> aa =
                        scene->create_gameobject("cube_" + std::to_string(cubeno++));
                    aa->add_component<Model>(cube_model);
                    aa->get_component<Transform>()->set_position(
                        glm::vec3(i*2, j*2, -5+k*2));
                    aa->add_component<Collider>(new BoxCollider(1, 1, 1));
                    aa->add_component<RigidBody>(new RigidBody(0.1));
                }
            }
        }

        std::shared_ptr<GameObject> cube = scene->create_gameobject("cube");
        cube->add_component<Model>(cube_model);
        cube->get_component<Transform>()->set_position(glm::vec3(1, 15, 0.0));

        std::shared_ptr<GameObject> scene_object = scene->create_gameobject("plane");
        scene_object->add_component<Model>(scene_model);
        scene_object->get_component<Transform>()->set_position(
            glm::vec3(0.0, -5, 0.0));
        scene_object->get_component<Transform>()->set_euler_rotation(glm::vec3(10, 0, 0));
        scene_object->get_component<Transform>()->set_scale(glm::vec3(1));
        scene_object->add_component<Collider>(new MeshCollider(*scene_model));
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
