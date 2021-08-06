#include <framebuffer.h>

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &id);
}

Framebuffer::Framebuffer(const Texture& texture)
{
    glGenFramebuffers(1, &id);
    attach_texture(texture);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &id);
}

void Framebuffer::attach_texture(const Texture& texture)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
}

void Framebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
