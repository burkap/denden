#pragma once

#include <texture.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
private:
    unsigned int id;
public:
    Framebuffer();
    Framebuffer(const Texture& texture);
    ~Framebuffer();
    void attach_texture(const Texture& texture);
    void bind();
    void unbind();
};
