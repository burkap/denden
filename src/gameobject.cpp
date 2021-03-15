#include <gameobject.h>

void GameObject::set_model(Model model) { mModel = model; }
void GameObject::set_transform(Transform transform) { this->transform = transform; }
void GameObject::draw(Shader &shader){
    mModel.draw(shader);
}