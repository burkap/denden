#ifndef GAMEOBJECT_H
#define GAMEOBJET_H
#include <model.h>
#include <shader.h>
#include <transform.h>

class GameObject {
   private:
    Model mModel;

   public:
    Transform transform;
    GameObject(Transform transform, Model model)
        : transform(transform), mModel(model) {}
    void set_model(Model model);
    void set_transform(Transform transform);
    void draw(Shader &shader);
};

#endif