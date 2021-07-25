#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <debugdrawer.h>

#include <vector>
class Physics {
   private:
    static Physics* instance;
    DebugDrawer* debug_drawer;
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* config;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* world;

   public:
    static Physics* the();
    std::vector<btRigidBody*> rbs;
    Physics();
    ~Physics();
    void init();
    void step(float t);
    void add_rigidbody(btRigidBody* rb);
    void remove_rigidbody(btRigidBody* rb);
    void draw();
    btDiscreteDynamicsWorld* get_world();
    DebugDrawer* get_debug_drawer() { return debug_drawer; }
};
