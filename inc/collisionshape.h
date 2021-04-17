#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H
#include <bullet/btBulletCollisionCommon.h>
#include <component.h>

#define FOREACH_SHAPE_TYPE(TYPE) \
    TYPE(Box)                    \
    TYPE(Sphere)                 \
    TYPE(Capsule)                \
    TYPE(Cylinder)               \
    TYPE(Cone)

#define GENERATE_ENUM(ENUM) ENUM,

enum class ShapeType { FOREACH_SHAPE_TYPE(GENERATE_ENUM) };

struct ShapeInfo {
    ShapeType type;
    btVector3 vec = btVector3(1, 1, 1);
    btScalar radius = 1;
    btScalar height = 1;
};

class CollisionShape : public Component {
    btCollisionShape* collision_shape;

   public:
    CollisionShape();
    CollisionShape(ShapeInfo info);
    ~CollisionShape();
    btCollisionShape* get_collision_shape();
    void set_collision_shape(btCollisionShape* cs);
};

#endif  // COLLISIONSHAPE_H
