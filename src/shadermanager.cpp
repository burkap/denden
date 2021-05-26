#include <shadermanager.h>
#include <configparser.h>
#include <util.h>

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::ShaderManager()
{
    ConfigParser config(get_exe_path()+"/shaders.ini");

    std::string default_vertex = config.get_value("Default", "vertex");
    std::string default_fragment = config.get_value("Default", "fragment");

    assert (default_vertex != CONF_NON_EXIST && default_fragment != CONF_NON_EXIST);
    m_default_shader = std::make_shared<Shader>(default_vertex.c_str(), default_fragment.c_str());

    std::string light_vertex = config.get_value("Light", "vertex");
    std::string light_fragment = config.get_value("Light", "fragment");

    assert (light_vertex != CONF_NON_EXIST && light_fragment != CONF_NON_EXIST);
    m_light_shader = std::make_shared<Shader>(light_vertex.c_str(), light_fragment.c_str());

    std::string cube_vertex = config.get_value("Cube", "vertex");
    std::string cube_fragment = config.get_value("Cube", "fragment");

    assert (cube_vertex != CONF_NON_EXIST && cube_fragment != CONF_NON_EXIST);
    m_skybox_shader = std::make_shared<Shader>(cube_vertex.c_str(), cube_fragment.c_str());

    std::string debug_vertex = config.get_value("Debug", "vertex");
    std::string debug_fragment = config.get_value("Debug", "fragment");

    assert (debug_vertex != CONF_NON_EXIST && debug_fragment != CONF_NON_EXIST);
    m_debug_shader = std::make_shared<Shader>(debug_vertex.c_str(), debug_fragment.c_str());
}

ShaderManager* ShaderManager::the()
{
    if(instance == nullptr){
            instance = new ShaderManager();
    }
    return instance;
}
