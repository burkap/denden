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

class CollisionShape : public Component {
   protected:
    btCollisionShape* collision_shape;
   public:
    CollisionShape();
    ~CollisionShape();
    btCollisionShape* create_mesh_shape(Model& model);
    btCollisionShape* get_collision_shape();
    void set_collision_shape(btCollisionShape* cs);
};

class BoxShape : public CollisionShape {
public:
    BoxShape(float x, float y, float z);
};

class SphereShape : public CollisionShape {
public:
    SphereShape(float radius);
};

class CapsuleShape : public CollisionShape {
public:
    CapsuleShape(float radius, float height);
};

class CylinderShape : public CollisionShape {
public:
    CylinderShape(float x, float y, float z);
};

class ConeShape : public CollisionShape {
public:
    ConeShape(float radius, float height);
};

class MeshShape : public CollisionShape {
public:
    MeshShape(Model model);
};

#endif  // COLLISIONSHAPE_H
