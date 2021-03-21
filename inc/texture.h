#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <iostream>
#include <string>

#define FOREACH_TEXTURE_TYPE(TEXTURE_TYPE) \
    TEXTURE_TYPE(Diffuse)                  \
    TEXTURE_TYPE(Specular)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum class TextureType { FOREACH_TEXTURE_TYPE(GENERATE_ENUM) };

TextureType aitex_to_ourtex(aiTextureType tex_type);
std::string type_to_string(TextureType tex_type);

struct Texture {
    TextureType type;
    int width, height, no_channels;
    unsigned int id;
    std::string path;
    Texture(std::string path, TextureType type) : path(path), type(type) {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data =
            stbi_load(path.c_str(), &width, &height, &no_channels, 0);
        std::cout << "width: " << width << " height: " << height
                  << " #channels: " << no_channels << " path: " << path.c_str()
                  << " type: " << type_to_string(type) << std::endl;
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Error while loading texture (" << path << ")\n";
        }
        stbi_image_free(data);
    }

    void bind() {
        // glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, id);
    }
};

#endif