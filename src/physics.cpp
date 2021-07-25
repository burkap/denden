#include <physics.h>
#include <globals.h>
#include <algorithm>

Physics* Physics::instance = nullptr;

Physics *Physics::the()
{
    if(instance == nullptr){
        instance = new Physics();
    }
    return instance;
}

Physics::Physics() {
    init();

    debug_drawer = new DebugDrawer();
    debug_drawer->setDebugMode(
        ((Globals::debug_draw_AABB) ? btIDebugDraw::DBG_DrawAabb : 0) +
        ((Globals::debug_draw_wireframe) ? btIDebugDraw::DBG_DrawWireframe
                                         : 0));
   world->setDebugDrawer(debug_drawer);
}

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

void Physics::remove_rigidbody(btRigidBody *rb)
{
    for(int i = 0; i < rbs.size(); i++){
        if(rbs[i] == rb){
            world->removeRigidBody(rb);
            btMotionState* ms = rb->getMotionState();
            delete rb;
            delete ms;
            rbs.erase(rbs.begin() + i);
            break;
        }
    }
}

void Physics::step(float t) { world->stepSimulation(t); }

void Physics::draw() { world->debugDrawWorld(); }

btDiscreteDynamicsWorld *Physics::get_world() { return world; }
