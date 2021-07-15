#pragma once
#include <component.h>
#include <transform.h>
#include <camera.h>

class PlayerLook : public Component{
    public:
        PlayerLook(){}
        PlayerLook(std::shared_ptr<Camera> camera) : camera(camera) {}
        std::shared_ptr<Camera> camera;
        double mouse_x;
        double mouse_y;

        double sens_x = 1.0;
        double sens_y = 1.0;
        double rotation_speed = 150.0;

        double x_rotation = 0;
        double y_rotation = 0;

    virtual void update(float dt);
};

