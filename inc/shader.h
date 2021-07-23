#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <glm/glm.hpp>
#include <string>

struct Shader {
    GLuint m_program;
    Shader(const char* vertex_path, const char* fragment_path);

    std::string read_shader(const char* path);
    GLuint compile_shader(const char* source, int shader_type);
    GLuint create_program(GLuint vs, GLuint fs);

    void use();

    void set_bool(const char* name, bool i);
    void set_int(const char* name, int i);
    void set_float(const char* name, float i);
    void set_vec3f(const char* name, const GLfloat& v1, const GLfloat& v2,
                   const GLfloat& v3);
    void set_vec4f(const char* name, const GLfloat& v1, const GLfloat& v2,
                   const GLfloat& v3, const GLfloat& v4);
    void set_mat4f(const char* name, const glm::mat4& v);
};
