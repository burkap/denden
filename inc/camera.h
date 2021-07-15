#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <component.h>

class Camera : public Component{
   private:
    glm::vec3 m_pos;
    glm::vec3 m_target;
    glm::vec3 m_up;
    float m_fov_angle;
    float m_aspect_ratio;
    float m_near;
    float m_far;

   public:
    double pitch_angle;
    double yaw_angle;
    Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fov_angle,
           float aspect_ratio, float near, float far);

    void set_pos(glm::vec3 val) { m_pos = val; }
    void set_target(glm::vec3 val) { m_target = val; }
    void set_up(glm::vec3 val) { m_up = val; }

    void set_euler_pitch_yaw(double yaw, double pitch);

    glm::vec3 get_pos() { return m_pos; }
    glm::vec3 get_target() { return m_target; }
    glm::vec3 get_up() { return m_up; }

    glm::mat4 get_view_matrix();

    glm::mat4 get_projection_matrix();
};

#endif
