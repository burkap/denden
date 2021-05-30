#ifndef COMPONENT_H
#define COMPONENT_H
#include <gameobject.h>

#include <iostream>
#include <memory>

class GameObject;

class Component {
   public:
    int id;
    GameObject* parent;
    Component();
    virtual void start() { /* do nothing */ }
    virtual void update(float dt) { /* do nothing */ }
    void set_parent(GameObject* ptr);
};

#endif  // COMPONENT_H
