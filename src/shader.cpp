#include <shader.h>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertex_source, const char* fragment_source) {
    GLuint vertex_shader = compile_shader(vertex_source, GL_VERTEX_SHADER);
    GLuint fragment_shader =
        compile_shader(fragment_source, GL_FRAGMENT_SHADER);
    m_program = create_program(vertex_shader, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

GLuint Shader::compile_shader(const char* source, int shader_type) {
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        printf("Failed to compile the %s shader.\n",
                (shader_type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
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

void Shader::set_vec3f(const char* name, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform3f(glGetUniformLocation(m_program, name), v1, v2, v3);
}

void Shader::set_mat4f(const char* name, glm::mat4 v) {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name), 1, GL_FALSE,
                        glm::value_ptr(v));
}