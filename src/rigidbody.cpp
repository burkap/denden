#include <bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <rigidbody.h>
#include <transform.h>
#include <physics.h>
#include <util.h>

RigidBody::RigidBody(){
}

RigidBody::RigidBody(double mass) : mass(mass) {
}

void RigidBody::set_mass(double m) {
    mass = m;
}
btRigidBody* RigidBody::create_rigidbody() {
    // TO-DO: This should only be called IF the object has both Transform and
    // Collider components
    transform = parent->get_component<Transform>();
    btTransform t;
    t.setIdentity();
    btVector3 initial_inertia(0, 0, 0);
    t.setOrigin(glm_to_bt_vec3(transform->get_position()));
    t.setRotation(glm_to_bt_quat(transform->get_quaternion()));
    btCollisionShape* plane =
        parent->get_component<Collider>()->get_collision_shape();

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

void RigidBody::update(float dt)
{
    btTransform to_set;
    to_set.setIdentity();
    to_set.setOrigin(glm_to_bt_vec3(transform->get_position()));
    to_set.setRotation(glm_to_bt_quat(transform->get_quaternion()));
    m_rigidbody->setWorldTransform(to_set);
    m_rigidbody->getMotionState()->setWorldTransform(to_set);
}

void RigidBody::freeze_rotation_x(bool b)
{
    m_freeze_rotation_x = b;
    update_freeze_rotation();
}

void RigidBody::freeze_rotation_y(bool b)
{
    m_freeze_rotation_y = b;
    update_freeze_rotation();
}

void RigidBody::freeze_rotation_z(bool b)
{
    m_freeze_rotation_z = b;
    update_freeze_rotation();
}

void RigidBody::update_freeze_rotation()
{
    m_rigidbody->setAngularFactor(btVector3(!m_freeze_rotation_x, !m_freeze_rotation_y, !m_freeze_rotation_z));
}
