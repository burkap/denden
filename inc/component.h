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
    virtual void* get_this() { return this; };
    void set_parent(GameObject* ptr);
};

class TestComponent : public Component {
   public:
    int kek;
    int x;
    int y;
    int z;
    TestComponent();

    virtual void* get_this() override { return this; }
};

#endif  // COMPONENT_H
