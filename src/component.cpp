#include <component.h>

#include <iostream>

Component::Component() { id = 1; }

void Component::set_parent(GameObject* ptr) { parent = ptr; }

TestComponent::TestComponent() {
    id = 2;
    kek = 42;
}
