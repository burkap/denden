#include <camera.h>
#include <util.h>

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up, float fov_angle,
               float aspect_ratio, float near, float far)
    : m_pos(pos),
      m_target(target),
      m_up(up),
      m_fov_angle(fov_angle),
      m_aspect_ratio(aspect_ratio),
      m_near(near),
      m_far(far) {}

void Camera::set_euler_pitch_yaw(double yaw, double pitch){
    m_target = euler_to_direction_vec(yaw, pitch);
}

glm::mat4 Camera::get_view_matrix() {
    return glm::lookAt(m_pos, m_pos + m_target, m_up);
}

glm::mat4 Camera::get_projection_matrix() {
    return glm::perspective(m_fov_angle, m_aspect_ratio, m_near, m_far);
}
