#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform {
   public:
    glm::vec3 m_position, m_rotation, m_scale;
    Transform()
        : m_position(glm::vec3(0, 0, 0)),
          m_rotation(glm::vec3(0, 0, 0)),
          m_scale(glm::vec3(1.0, 1.0, 1.0)) {}
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
        : m_position(position), m_rotation(rotation), m_scale(scale) {}

    glm::mat4 get_model_matrix() {
        glm::mat4 matrix(1.0f);
        matrix = glm::translate(matrix, m_position);
        matrix = glm::rotate(matrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        matrix = glm::rotate(matrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        matrix = glm::rotate(matrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        matrix = glm::scale(matrix, m_scale);
        return matrix;
    }

    glm::vec3 get_position() { return m_position; }
    glm::vec3 get_rotation() { return m_rotation; }
    glm::vec3 get_scale() { return m_scale; }

    void set_position(glm::vec3 val) { m_position = val; }
    void set_rotation(glm::vec3 val) { m_rotation = val; }
    void set_scale(glm::vec3 val) { m_scale = val; }

   private:
};

#endif