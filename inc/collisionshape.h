#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H
#include <bullet/btBulletCollisionCommon.h>
#include <component.h>

class CollisionShape : public Component {
    btCollisionShape* collision_shape;

   public:
    CollisionShape();
    ~CollisionShape();
    btCollisionShape* get_collision_shape();
    void set_collision_shape(btCollisionShape* cs);
};

#endif  // COLLISIONSHAPE_H
