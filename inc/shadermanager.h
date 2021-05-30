#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <shader.h>
#include <memory>

class ShaderManager
{
protected:
    static ShaderManager* instance;
    std::shared_ptr<Shader> m_default_shader;
    std::shared_ptr<Shader> m_light_shader;
    std::shared_ptr<Shader> m_skybox_shader;
    std::shared_ptr<Shader> m_debug_shader;
public:
    ShaderManager();
    void set_default_shader(std::shared_ptr<Shader> s) { m_default_shader = s; }
    void set_light_shader(std::shared_ptr<Shader> s) { m_light_shader = s; }
    void set_skybox_shader(std::shared_ptr<Shader> s) { m_skybox_shader = s; }
    void set_debug_shader(std::shared_ptr<Shader> s) { m_debug_shader = s; }

    std::shared_ptr<Shader> get_default_shader() { return m_default_shader; }
    std::shared_ptr<Shader> get_light_shader() { return m_light_shader; }
    std::shared_ptr<Shader> get_skybox_shader() { return m_skybox_shader; }
    std::shared_ptr<Shader> get_debug_shader() { return m_debug_shader; }


    static ShaderManager* the();
    // not cloneable
    ShaderManager(ShaderManager &other) = delete;
    // not assignable
    void operator=(const ShaderManager &) = delete;
};

#endif // SHADERMANAGER_H
