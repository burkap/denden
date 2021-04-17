#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <bullet/BulletCollision/CollisionShapes/btConeShape.h>
#include <bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <collisionshape.h>

CollisionShape::CollisionShape() {
    collision_shape = new btBoxShape(btVector3(16, 0, 16));
}

CollisionShape::CollisionShape(ShapeInfo info) {
    switch (info.type) {
        case ShapeType::Box:
            collision_shape = new btBoxShape(info.vec);
            break;
        case ShapeType::Sphere:
            collision_shape = new btSphereShape(info.radius);
            break;
        case ShapeType::Capsule:
            collision_shape = new btCapsuleShape(info.radius, info.height);
            break;
        case ShapeType::Cylinder:
            collision_shape = new btCylinderShape(info.vec);
            break;
        case ShapeType::Cone:
            collision_shape = new btConeShape(info.radius, info.height);
            break;
    }
}

CollisionShape::~CollisionShape() { delete collision_shape; }

btCollisionShape* CollisionShape::get_collision_shape() {
    return collision_shape;
}
void CollisionShape::set_collision_shape(btCollisionShape* cs) {
    collision_shape = cs;
}
