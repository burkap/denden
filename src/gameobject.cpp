#include <gameobject.h>
#include <typeinfo>
#include <components/componentlist.h>

unsigned int GameObject::count = 0;

GameObject::GameObject() { id = count++; }

GameObject::GameObject(std::string val) : GameObject() { name = val; }

template <typename T>
std::shared_ptr<T> GameObject::add_component(T* t /* = new T() */) {
    std::shared_ptr<T> new_component = std::shared_ptr<T>(t);
    components[typeid(T)] = new_component;
    components[typeid(T)]->set_parent(this);
    t->start();
    return new_component;
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
