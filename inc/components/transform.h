#pragma once
#include <components/component.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

inline glm::vec3 euler_to_radians(glm::vec3 v){
    float ratio = glm::pi<double>() / 180.f;
    return v * ratio;
}

inline glm::vec3 xyz_to_zyx(glm::vec3 v){
    return glm::vec3(v.z, v.y, v.x);
}

class Transform : public Component {
   public:
    glm::vec3 m_position, m_euler_rot, m_scale;
    glm::quat m_quaternion;
    Transform()
        : m_position(glm::vec3(0, 0, 0)),
          m_euler_rot(glm::vec3(0, 0, 0)),
          m_scale(glm::vec3(1.0, 1.0, 1.0)),
          m_quaternion(glm::quat(1.0, 0.0, 0.0, 0.0)) {}
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : m_position(position), m_euler_rot(rotation), m_scale(scale), m_quaternion(glm::quat(xyz_to_zyx(euler_to_radians(rotation)))) {
    }

    glm::mat4 get_model_matrix() {
        glm::mat4 matrix(1.0f);
        matrix = glm::translate(matrix, m_position);
        matrix = matrix * glm::mat4_cast(m_quaternion);
        matrix = glm::scale(matrix, m_scale);
        return matrix;
    }

    glm::vec3 get_position() { return m_position; }
    glm::vec3 get_euler_rotation() { return m_euler_rot; }
    glm::vec3 get_scale() { return m_scale; }
    glm::quat get_quaternion() { return m_quaternion; }
    glm::vec3 forward() {
        glm::vec3 vec;
        vec.x = 2 * (m_quaternion.x * m_quaternion.z + m_quaternion.w * m_quaternion.y);
        vec.y = 2 * (m_quaternion.y * m_quaternion.z - m_quaternion.w * m_quaternion.x);
        vec.z = 1 - (2 * (m_quaternion.x * m_quaternion.x + m_quaternion.y * m_quaternion.y));
        return vec;
    }

    glm::vec3 up() {
        glm::vec3 vec;
        vec.x = 2 * (m_quaternion.x * m_quaternion.y - m_quaternion.w * m_quaternion.z);
        vec.y = 1 - (2 * (m_quaternion.x * m_quaternion.x + m_quaternion.z * m_quaternion.z));
        vec.z = 2 * (m_quaternion.y * m_quaternion.z + m_quaternion.w * m_quaternion.x);
        return vec;
    }
    glm::vec3 left() {
        glm::vec3 vec;
        vec.x = 1 - (2 * (m_quaternion.y * m_quaternion.y + m_quaternion.z * m_quaternion.z));
        vec.y = 2 * (m_quaternion.x * m_quaternion.y + m_quaternion.w * m_quaternion.z);
        vec.z = 2 * (m_quaternion.x * m_quaternion.z - m_quaternion.w * m_quaternion.y);
        return vec;
    }

    void set_position(glm::vec3 val) { m_position = val; }
    void set_euler_rotation(glm::vec3 val) {
        m_euler_rot = val;
        m_quaternion = glm::quat(xyz_to_zyx(euler_to_radians(m_euler_rot)));
    }
    void set_scale(glm::vec3 val) { m_scale = val; }
    void set_quaternion(glm::quat val) { m_quaternion = val; }

    void on_change();
   private:
};
