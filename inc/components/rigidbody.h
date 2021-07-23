#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <components/collider.h>
#include <components/transform.h>

class RigidBody : public Component {
    btTransform tf;
    double mass = 0;
    btRigidBody::btRigidBodyConstructionInfo* info;
    btRigidBody* m_rigidbody;
    std::shared_ptr<Transform> transform;
    std::shared_ptr<Collider> collision_shape;
    bool m_freeze_rotation_x = false;
    bool m_freeze_rotation_y = false;
    bool m_freeze_rotation_z = false;

   public:
    RigidBody();
    RigidBody(double mass);
    void set_mass(double m);
    btRigidBody* create_rigidbody();
    btRigidBody* get_rigidbody();
    void freeze_rotation_x(bool b);
    void freeze_rotation_y(bool b);
    void freeze_rotation_z(bool b);
    void update_freeze_rotation();
    void add_force(glm::vec3 f);

    void set_parent(GameObject* ptr) override;
    void update(float dt) override;
};
