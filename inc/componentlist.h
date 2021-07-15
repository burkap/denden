#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H
#include <collider.h>
#include <model.h>
#include <rigidbody.h>
#include <transform.h>
#include <camera.h>
#include <components/lambdascript.h>
#include <components/fps_example/playerlook.h>

#define FOREACH_COMPONENT_TYPE(COMPONENT_TYPE) \
    COMPONENT_TYPE(Transform)                  \
    COMPONENT_TYPE(Model)                      \
    COMPONENT_TYPE(RigidBody)                  \
    COMPONENT_TYPE(Collider)                   \
    COMPONENT_TYPE(LambdaScript)               \
    COMPONENT_TYPE(Camera)                     \
    COMPONENT_TYPE(PlayerLook)                 \

#define ADD_COMPONENT(x) template std::shared_ptr<x> GameObject::add_component<x>(x* a);
#define ADD_COMPONENT_A(x) template void GameObject::add_component<x>(x & a);

#define GET_COMPONENT(x) \
    template std::shared_ptr<x> GameObject::get_component<x>();

#endif // COMPONENTLIST_H
