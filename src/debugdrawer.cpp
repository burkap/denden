#include <debugdrawer.h>
#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

DebugDrawer::DebugDrawer() : m_debugMode(0) {
    //
}

DebugDrawer::~DebugDrawer() { std::cout << "do nothing\n"; }

void DebugDrawer::set_view(glm::mat4 v) { view = v; }
void DebugDrawer::set_projection(glm::mat4 p) { projection = p; }

void DebugDrawer::set_shader(std::shared_ptr<Shader> shader) { debug_shader = shader; }

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
                           const btVector3 &fromColor,
                           const btVector3 &toColor) {
    //
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to,
                           const btVector3 &color) {
    lines.push_back(Line(from, to, color, color));
}

void DebugDrawer::drawSphere(const btVector3 &p, btScalar radius,
                             const btVector3 &color) {
    //
}

void DebugDrawer::drawTriangle(const btVector3 &a, const btVector3 &b,
                               const btVector3 &c, const btVector3 &color,
                               btScalar alpha) {
    //
}

void DebugDrawer::drawContactPoint(const btVector3 &PointOnB,
                                   const btVector3 &normalOnB,
                                   btScalar distance, int lifeTime,
                                   const btVector3 &color) {
    //
}

void DebugDrawer::reportErrorWarning(const char *warningString) {
    std::cout << warningString;
}

void DebugDrawer::draw3dText(const btVector3 &location,
                             const char *textString) {
    //
}

void DebugDrawer::setDebugMode(int debugMode) { m_debugMode = debugMode; }

void DebugDrawer::drawAll() {
    debug_shader->use();
    debug_shader->set_mat4f("view", view);
    debug_shader->set_mat4f("projection", projection);
    debug_shader->set_vec3f("color", 1.0, 0.0, 0.0);

    unsigned int vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Line) * lines.size(), &lines[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, lines.size() * 2);
    glDeleteBuffers(1, &vbo);
    lines.clear();
}
