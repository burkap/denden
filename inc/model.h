#ifndef MODEL_H
#define MODEL_H
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <shader.h>
#include <texture.h>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texture;
    void print() {
        std::cout << "\nVertex: " << this << "\n";
        std::cout << "Pos: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
        std::cout << "Normal: " << normal.x << ", " << normal.y << ", "
                  << normal.z << "\n";
        std::cout << "Texture: " << texture.x << ", " << texture.y << "\n";
    }
};

class Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO, VBO, EBO;

   public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices,
         std::vector<Texture> textures);

    void setup_mesh();

    void draw(Shader &shader);
};

class Model {
    std::vector<Mesh> meshes;
    std::vector<Texture> texture_cache;

   public:
    void load_model(std::string path);
    void process_node(aiNode *node, const aiScene *scene);
    std::vector<Texture> load_textures(aiMaterial *mat, aiTextureType tex_type);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    void set_meshes(std::vector<Mesh> new_meshes);
    void draw(Shader &shader);
};
#endif
