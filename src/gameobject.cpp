#include <gameobject.h>

void GameObject::set_model(Model model) { m_Model = model; }
void GameObject::set_transform(Transform transform) {
    this->transform = transform;
}
void GameObject::draw(Shader &shader) { m_Model.draw(shader); }
