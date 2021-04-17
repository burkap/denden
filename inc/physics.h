#ifndef PHYSICS_H
#define PHYSICS_H
#include <bullet/btBulletDynamicsCommon.h>

#include <vector>
class Physics {
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* config;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;

   public:
    std::vector<btRigidBody*> rbs;
    Physics();
    ~Physics();
    void init();
    void step(float t);
    void add_rigidbody(btRigidBody* rb);
    void draw();
    btDiscreteDynamicsWorld* get_world();
};

#endif  // PHYSICS_H
