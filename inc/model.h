#ifndef MODEL_H
#define MODEL_H
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <shader.h>

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    Vertex(glm::vec3 p, glm::vec3 c) : pos(p), color(c) {}
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