#include <lightobject.h>

int PointLight::count = 0;

void PointLight::apply(Shader &shader) {
    char str[64];
    sprintf(str, "pointLights[%i].ambient", id);
    shader.set_vec3f(str, ambient.x, ambient.y, ambient.z);
    sprintf(str, "pointLights[%i].diffuse", id);
    shader.set_vec3f(str, diffuse.x, diffuse.y, diffuse.z);
    sprintf(str, "pointLights[%i].specular", id);
    shader.set_vec3f(str, specular.x, specular.y, specular.z);

    sprintf(str, "pointLights[%i].constant", id);
    shader.set_float(str, constant);
    sprintf(str, "pointLights[%i].linear", id);
    shader.set_float(str, linear);
    sprintf(str, "pointLights[%i].quadratic", id);
    shader.set_float(str, quadratic);

    sprintf(str, "pointLights[%i].position", id);
    shader.set_vec3f(str, get_component<Transform>()->m_position.x, get_component<Transform>()->m_position.y,
                     get_component<Transform>()->m_position.z);
}
