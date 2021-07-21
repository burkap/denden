#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <components/component.h>
#include <shader.h>

#include <memory>
#include <typeindex>
#include <unordered_map>

class Component;
class GameObject {
   private:
   public:
    unsigned int id;
    static unsigned int count;
    std::string name;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    GameObject();
    GameObject(std::string val);
    template <typename T>
    std::shared_ptr<T> add_component(T* t = new T());
    template <typename T>
    void add_component(T &a);
    template <typename T>
    std::shared_ptr<T> get_component();
};

#endif
