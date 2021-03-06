#pragma once
#include <components/collider.h>
#include <components/model.h>
#include <components/rigidbody.h>
#include <components/transform.h>
#include <components/camera.h>
#include <components/lambdascript.h>
#include <components/template.h>
#include <components/fps_example/playerlook.h>

#define FOREACH_COMPONENT_TYPE(COMPONENT_TYPE) \
    COMPONENT_TYPE(Transform)                  \
    COMPONENT_TYPE(Model)                      \
    COMPONENT_TYPE(RigidBody)                  \
    COMPONENT_TYPE(Collider)                   \
    COMPONENT_TYPE(LambdaScript)               \
    COMPONENT_TYPE(Camera)                     \
    COMPONENT_TYPE(TemplateComponent)          \
    COMPONENT_TYPE(PlayerLook)                 \

#define ADD_COMPONENT(x) template std::shared_ptr<x> GameObject::add_component<x>(x* a);
#define ADD_COMPONENT_A(x) template void GameObject::add_component<x>(x & a);

#define GET_COMPONENT(x) \
    template std::shared_ptr<x> GameObject::get_component<x>();
