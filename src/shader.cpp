#include <libgen.h>
#include <shader.h>
#include <util.h>

#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

Shader::Shader(const char* vertex_path, const char* fragment_path) {
    std::string vertex_source = read_shader(vertex_path);
    std::string fragment_source = read_shader(fragment_path);
    GLuint vertex_shader =
        compile_shader(vertex_source.c_str(), GL_VERTEX_SHADER);
    GLuint fragment_shader =
        compile_shader(fragment_source.c_str(), GL_FRAGMENT_SHADER);
    m_program = create_program(vertex_shader, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

std::string Shader::read_shader(const char* path) {
    std::stringstream stream;
    std::fstream file;
    char actual_path[PATH_MAX];
    strcpy(actual_path, get_exe_path());
    strcat(actual_path, "/");
    strcat(actual_path, path);
    file.open(actual_path);
    stream << file.rdbuf();
    file.close();
    return stream.str();
}

GLuint Shader::compile_shader(const char* source, int shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;
    GLchar log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        printf("Failed to compile the %s shader.\n",
               (shader_type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        printf(log);
    }
    return shader;
}

GLuint Shader::create_program(GLuint vs, GLuint fs) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        printf("Failed to create the shader program.\n");
    }
    return program;
}

void Shader::use() { glUseProgram(m_program); }


void Shader::set_int(const char* name, int i) {
    glUniform1i(glGetUniformLocation(m_program, name), i);
}

void Shader::set_vec3f(const char* name, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform3f(glGetUniformLocation(m_program, name), v1, v2, v3);
}

void Shader::set_vec4f(const char* name, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) {
    glUniform4f(glGetUniformLocation(m_program, name), v1, v2, v3, v4);
}

void Shader::set_mat4f(const char* name, glm::mat4 v) {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE,
                       glm::value_ptr(v));
}