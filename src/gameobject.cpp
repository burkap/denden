#include <gameobject.h>
#include <typeinfo>
#include <transform.h>
#include <model.h>

unsigned int GameObject::count = 0;

GameObject::GameObject() {
    id = count++;
}

GameObject::GameObject(std::string val) : GameObject()
{
    name = val;
}

template<typename T>
void GameObject::add_component()
{
    components[typeid(T)] = std::shared_ptr<T>(new T());
}

template void GameObject::add_component<Component>();
template void GameObject::add_component<TestComponent>();
template void GameObject::add_component<Transform>();
template void GameObject::add_component<Model>();
template<typename T>
void GameObject::add_component(T &a)
{
    components[typeid(T)] = std::shared_ptr<T>(&a);
}

template void GameObject::add_component<Component>(Component &a);
template void GameObject::add_component<TestComponent>(TestComponent &a);
template void GameObject::add_component<Transform>(Transform &a);
template void GameObject::add_component<Model>(Model &a);

template<typename T>

std::shared_ptr<T> GameObject::get_component()
{
    if (components.find(typeid(T)) == components.end()) return nullptr;
    return std::dynamic_pointer_cast<T>(components[typeid(T)]);
}

template std::shared_ptr<TestComponent> GameObject::get_component<TestComponent>();
template std::shared_ptr<Transform> GameObject::get_component<Transform>();
template std::shared_ptr<Model> GameObject::get_component<Model>();
