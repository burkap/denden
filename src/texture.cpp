#include <texture.h>
#define GENERATE_CASE(x) \
    case TextureType::x: \
        return #x;

TextureType aitex_to_ourtex(aiTextureType tex_type) {
    switch (tex_type) {
        case aiTextureType_DIFFUSE:
            return TextureType::Diffuse;
        case aiTextureType_SPECULAR:
            return TextureType::Specular;
        default:
            std::cout << "something went wrong aitex\n";
            return TextureType::Diffuse;
    }
}

std::string type_to_string(TextureType tex_type) {
    switch (tex_type) { FOREACH_TEXTURE_TYPE(GENERATE_CASE) }
}