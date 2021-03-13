#ifndef MODEL_H
#define MODEL_H
#include <shader.h>

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
    void set_meshes(std::vector<Mesh> new_meshes);
    void draw();
};
#endif