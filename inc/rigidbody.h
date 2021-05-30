#ifndef RIGIDBODY_H
#define RIGIDBODY_H
#include <bullet/btBulletDynamicsCommon.h>
#include <collisionshape.h>
#include <transform.h>

class RigidBody : public Component {
    btTransform tf;
    double mass = 0;
    btRigidBody::btRigidBodyConstructionInfo* info;
    btRigidBody* m_rigidbody;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<CollisionShape> collision_shape;

   public:
    RigidBody();
    void set_mass(double m);
    btRigidBody* create_rigidbody();
    btRigidBody* get_rigidbody();
};

#endif  // RIGIDBODY_H
