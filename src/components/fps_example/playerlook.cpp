#include <components/fps_example/playerlook.h>
#include <input.h>
#include <util.h>

void PlayerLook::update(float dt){
    mouse_x = Input::get_mouse_diff_x();
    mouse_y = Input::get_mouse_diff_y();

    x_rotation -= mouse_x * sens_x * rotation_speed;
    y_rotation -= mouse_y * sens_y * rotation_speed;
    y_rotation = glm::clamp(y_rotation, -90.0, 90.0);
    camera->set_euler_pitch_yaw(x_rotation, y_rotation);
}
