#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <model.h>
#include <shader.h>
#include <transform.h>

class GameObject {
   private:
    Model m_Model;

   public:
    Transform transform;
    GameObject(Transform transform, Model model)
        : transform(transform), m_Model(model) {}
    GameObject(Model model)
        : m_Model(model) {}
    GameObject();
    void set_model(Model model);
    void set_transform(Transform transform);
    void draw(Shader &shader);
};

#endif