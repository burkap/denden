#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <model.h>
#include <shader.h>
#include <transform.h>
#include <component.h>

#include <unordered_map>
#include <typeindex>
#include <memory>

class GameObject {
   private:

   public:
    unsigned int id;
    static unsigned int count;
    std::string name;
    std::unordered_map<std::type_index, std::shared_ptr<Component>> components;
    GameObject();
    GameObject(std::string val);
    template <typename T> void add_component();
    template <typename T> void add_component(T &a);
    template <typename T> std::shared_ptr<T> get_component();
};

#endif
