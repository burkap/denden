#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H
#include <bullet/btBulletCollisionCommon.h>
#include <component.h>
#include <model.h>

#define FOREACH_SHAPE_TYPE(TYPE) \
    TYPE(Box)                    \
    TYPE(Sphere)                 \
    TYPE(Capsule)                \
    TYPE(Cylinder)               \
    TYPE(Cone)                   \
    TYPE(Mesh)

#define GENERATE_ENUM(ENUM) ENUM,

enum class ShapeType { FOREACH_SHAPE_TYPE(GENERATE_ENUM) };

struct ShapeInfo {
    ShapeType type;
    btVector3 vec = btVector3(1, 1, 1);
    btScalar radius = 1;
    btScalar height = 1;
    Model model;
};

class CollisionShape : public Component {
    btCollisionShape* collision_shape;

   public:
    CollisionShape();
    CollisionShape(ShapeInfo info);
    ~CollisionShape();
    btCollisionShape* create_mesh_shape(Model& model);
    btCollisionShape* get_collision_shape();
    void set_collision_shape(btCollisionShape* cs);
};

#endif  // COLLISIONSHAPE_H
