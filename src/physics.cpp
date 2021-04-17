#include <physics.h>
Physics::Physics() {}

Physics::~Physics() {
    delete world;
    delete solver;
    delete config;
    delete dispatcher;
    delete broadphase;
}

void Physics::init() {
    broadphase = new btDbvtBroadphase();

    config = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(config);

    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, config);

    world->setGravity(btVector3(0, -9.8, 0));
}

void Physics::add_rigidbody(btRigidBody *rb) {
    rbs.push_back(rb);
    world->addRigidBody(rb);
}

void Physics::set_debug_drawer(DebugDrawer *db) { world->setDebugDrawer(db); }

void Physics::step(float t) { world->stepSimulation(t); }

void Physics::draw() { world->debugDrawWorld(); }

btDiscreteDynamicsWorld *Physics::get_world() { return world; }
