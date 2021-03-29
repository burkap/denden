#ifndef COMPONENT_H
#define COMPONENT_H
#include <iostream>

class Component
{
public:
    int id;
    Component();
    virtual void* get_this() { return this; };
};

class TestComponent : public Component
{
public:
    int kek;
    int x;
    int y;
    int z;
    TestComponent();

    virtual void* get_this() override{
        return this;
    }
};

#endif // COMPONENT_H
