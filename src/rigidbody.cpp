#include <bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <rigidbody.h>
#include <transform.h>
#include <physics.h>

RigidBody::RigidBody(){
}

RigidBody::RigidBody(double mass) : mass(mass) {
}

void RigidBody::set_mass(double m) {
    mass = m;
}
btRigidBody* RigidBody::create_rigidbody() {
    // TO-DO: This should only be called IF the object has both Transform and
    // CollisionShape components
    btTransform t;
    t.setIdentity();
    btVector3 initial_inertia(0, 0, 0);
    std::shared_ptr<Transform> tt = parent->get_component<Transform>();
    glm::vec3 pos = tt->get_position();
    t.setOrigin(btVector3(pos.x, pos.y, pos.z));
    btCollisionShape* plane =
        parent->get_component<CollisionShape>()->get_collision_shape();

    btMotionState* motion = new btDefaultMotionState();
    motion->setWorldTransform(t);

    plane->calculateLocalInertia(mass, initial_inertia);
    info = new btRigidBody::btRigidBodyConstructionInfo(btScalar(mass), motion,
                                                        plane, initial_inertia);
    info->m_friction = 1.0f;
    m_rigidbody = new btRigidBody(*info);
    Physics::the()->add_rigidbody(m_rigidbody);
    return m_rigidbody;
}

btRigidBody* RigidBody::get_rigidbody() { return m_rigidbody; }
void RigidBody::set_parent(GameObject* ptr) { parent = ptr;
                                              create_rigidbody();
                                            }
