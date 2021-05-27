#include <collisionshape.h>
#include <gameobject.h>
#include <model.h>
#include <rigidbody.h>
#include <transform.h>
#include <components/lambdascript.h>
#include <typeinfo>
#include <camera.h>

#define FOREACH_COMPONENT_TYPE(COMPONENT_TYPE) \
    COMPONENT_TYPE(Transform)                  \
    COMPONENT_TYPE(Model)                      \
    COMPONENT_TYPE(RigidBody)                  \
    COMPONENT_TYPE(CollisionShape)             \
    COMPONENT_TYPE(LambdaScript)               \

#define ADD_COMPONENT(x) template void GameObject::add_component<x>(x* a);
#define ADD_COMPONENT_A(x) template void GameObject::add_component<x>(x & a);

#define GET_COMPONENT(x) \
    template std::shared_ptr<x> GameObject::get_component<x>();
unsigned int GameObject::count = 0;

GameObject::GameObject() { id = count++; }

GameObject::GameObject(std::string val) : GameObject() { name = val; }

template <typename T>
void GameObject::add_component(T* t /* = new T() */) {
    components[typeid(T)] = std::shared_ptr<T>(t);
    components[typeid(T)]->set_parent(this);
    t->start();
}

FOREACH_COMPONENT_TYPE(ADD_COMPONENT)

template <typename T>
void GameObject::add_component(T &a) {
    components[typeid(T)] = std::shared_ptr<T>(&a);
    components[typeid(T)]->set_parent(this);
    a.start();
}

FOREACH_COMPONENT_TYPE(ADD_COMPONENT_A)

template <typename T>

std::shared_ptr<T> GameObject::get_component() {
    if (components.find(typeid(T)) == components.end()) return nullptr;
    return std::dynamic_pointer_cast<T>(components[typeid(T)]);
}

FOREACH_COMPONENT_TYPE(GET_COMPONENT)
