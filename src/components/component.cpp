#include <components/component.h>

#include <iostream>

Component::Component() { id = 1; }

void Component::set_parent(GameObject* ptr) { parent = ptr; }

