#pragma once
#include <components/component.h>
#include <components/transform.h>
#include <components/camera.h>

class PlayerLook : public Component{
    public:
        PlayerLook(){}
        PlayerLook(std::shared_ptr<Camera> camera) : camera(camera) {}
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Transform> player_transform;
        double mouse_x;
        double mouse_y;

        double sens_x = 1.0;
        double sens_y = 1.0;
        double rotation_speed = 300.0;

        double x_rotation = 0;
        double y_rotation = 0;

        virtual void start();
        virtual void update(float dt);
};

