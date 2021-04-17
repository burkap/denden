#include <bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <collisionshape.h>

CollisionShape::CollisionShape() {
    //      collision_shape = new btStaticPlaneShape(btVector3(0,1,0), 0);
    collision_shape = new btBoxShape(btVector3(16, 0, 16));
}

CollisionShape::~CollisionShape() { delete collision_shape; }

btCollisionShape* CollisionShape::get_collision_shape() {
    return collision_shape;
}
void CollisionShape::set_collision_shape(btCollisionShape* cs) {
    collision_shape = cs;
}
