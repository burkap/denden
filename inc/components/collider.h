#pragma once
#include <bullet/btBulletCollisionCommon.h>
#include <components/component.h>
#include <components/model.h>

#define FOREACH_SHAPE_TYPE(TYPE) \
    TYPE(Box)                    \
    TYPE(Sphere)                 \
    TYPE(Capsule)                \
    TYPE(Cylinder)               \
    TYPE(Cone)                   \
    TYPE(Mesh)

#define GENERATE_ENUM(ENUM) ENUM,

enum class ShapeType { FOREACH_SHAPE_TYPE(GENERATE_ENUM) };

class Collider : public Component {
   protected:
    btCollisionShape* collision_shape;
   public:
    Collider();
    ~Collider();
    btCollisionShape* create_mesh_shape(Model& model);
    btCollisionShape* get_collision_shape();
    void set_collision_shape(btCollisionShape* cs);
};

class BoxCollider : public Collider {
public:
    BoxCollider(float x, float y, float z);
};

class SphereCollider : public Collider {
public:
    SphereCollider(float radius);
};

class CapsuleCollider : public Collider {
public:
    CapsuleCollider(float radius, float height);
};

class CylinderCollider: public Collider {
public:
    CylinderCollider(float x, float y, float z);
};

class ConeCollider : public Collider {
public:
    ConeCollider(float radius, float height);
};

class MeshCollider : public Collider {
public:
    MeshCollider(Model model);
};
