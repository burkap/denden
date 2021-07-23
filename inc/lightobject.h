#pragma once
#include <gameobject.h>

#include <string>

class LightObject : public GameObject {
   public:
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 ambient, diffuse, specular;
    LightObject() : GameObject("unnamed") {}
    LightObject(std::string name) : GameObject(name) {}
    void set_ambient(glm::vec3 v) { ambient = v; }
    void set_diffuse(glm::vec3 v) { diffuse = v; }
    void set_specular(glm::vec3 v) { specular = v; }
    virtual void apply(std::shared_ptr<Shader> shader) {
        std::cout << "Can't call apply() on base class LightObject\n";
    };
};

class DirectionalLight : public LightObject {
    glm::vec3 direction;

public:
    DirectionalLight(){}

    DirectionalLight(std::string name) : LightObject(name) {}

    void set_direction(glm::vec3 v) { direction = v; }
    glm::vec3 get_direction() { return direction; }

    void apply(std::shared_ptr<Shader> shader);
};

class PointLight : public LightObject {
    unsigned int id;
    float constant, linear, quadratic;

   public:
    static int count;

    PointLight() {
        id = count;
        count++;
        constant = 1.0f;
        linear = 0.09f;
        quadratic = 0.032f;
    }

    PointLight(std::string name) : LightObject(name) {
        id = count;
        count++;
        constant = 1.0f;
        linear = 0.09f;
        quadratic = 0.032f;
    }

    void set_attenuation(float c, float l, float q) {
        constant = c;
        linear = l;
        quadratic = q;
    }

    glm::vec3 set_attenuation() {
        return glm::vec3(constant, linear, quadratic);
    }

    void set_constant(float v) { constant = v; }
    void set_linear(float v) { linear = v; }
    void set_quadratic(float v) { quadratic = v; }

    float get_constant() { return constant; }
    float get_linear() { return linear; }
    float get_quadratic() { return quadratic; }

    void apply(std::shared_ptr<Shader> shader);
};
