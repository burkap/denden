#ifndef MODEL_H
#define MODEL_H
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <shader.h>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 texture;
    void print(){
        std::cout << "\nVertex: " << this << "\n";
        std::cout << "Pos: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
        std::cout << "Normal: " << normal.x << ", " << normal.y << ", " << normal.z << "\n";
        std::cout << "Texture: " << texture.x << ", " << texture.y << "\n";
    }
};

class Mesh {
    std::vector<Vertex> vertices;
    unsigned int VAO, VBO;

   public:
    Mesh(std::vector<Vertex> vertices);

    void setup_mesh();

    void draw();
};

class Model {
    std::vector<Mesh> meshes;

   public:
    void load_model(std::string path);
    void process_node(aiNode *node, const aiScene *scene);
    Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
    void set_meshes(std::vector<Mesh> new_meshes);
    void draw();
};
#endif