#ifndef DEBUGDRAWER_H
#define DEBUGDRAWER_H
#include <bullet/btBulletDynamicsCommon.h>
#include <shader.h>

#include <vector>
#include <memory>

struct Line {
    float x0, y0, z0;
    float r0, g0, b0;
    float x1, y1, z1;
    float r1, g1, b1;

    Line(btVector3 f, btVector3 t, btVector3 fc, btVector3 tc) {
        x0 = f.getX();
        y0 = f.getY();
        z0 = f.getZ();

        r0 = tc.getX();
        g0 = tc.getY();
        b0 = tc.getZ();

        x1 = t.getX();
        y1 = t.getY();
        z1 = t.getZ();

        r1 = fc.getX();
        g1 = fc.getY();
        b1 = fc.getZ();
    }
};

class DebugDrawer : public btIDebugDraw {
    int m_debugMode;
    unsigned int line_VAO, line_VBO;
    std::shared_ptr<Shader> debug_shader;
    glm::mat4 view, projection;
    std::vector<Line> lines;

   public:
    DebugDrawer();
    virtual ~DebugDrawer();
    void set_view(glm::mat4 v);
    void set_projection(glm::mat4 p);
    void set_shader(std::shared_ptr<Shader> shader);
    virtual void drawLine(const btVector3& from, const btVector3& to,
                          const btVector3& fromColor, const btVector3& toColor);

    virtual void drawLine(const btVector3& from, const btVector3& to,
                          const btVector3& color);

    virtual void drawSphere(const btVector3& p, btScalar radius,
                            const btVector3& color);

    virtual void drawTriangle(const btVector3& a, const btVector3& b,
                              const btVector3& c, const btVector3& color,
                              btScalar alpha);

    virtual void drawContactPoint(const btVector3& PointOnB,
                                  const btVector3& normalOnB, btScalar distance,
                                  int lifeTime, const btVector3& color);

    virtual void reportErrorWarning(const char* warningString);

    virtual void draw3dText(const btVector3& location, const char* textString);

    virtual void setDebugMode(int debugMode);

    virtual int getDebugMode() const { return m_debugMode; }

    void drawAll();
};

#endif  // DEBUGDRAWER_H
