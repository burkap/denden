#pragma once
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
    virtual void set_parent(GameObject* ptr);
};
