#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <model.h>

Mesh::Mesh(std::vector<Vertex> vertices) : vertices(vertices) { setup_mesh(); }

void Mesh::setup_mesh() {
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                 &vertices[0], GL_STATIC_DRAW);
    // parameters respectively:
    // --------------
    // index (location in shader)
    // array length
    // array type
    // normalize?
    // size (in bytes) of each vertex
    // offset (inside the boundaries of the vertex)
    // ---------------------
    // position (x, y, z) location = 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);
    // // color (r, g, b) location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(1);
    
    glBindVertexArray(0);
}

void Mesh::draw(){

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Model::set_meshes(std::vector<Mesh> new_meshes){
    meshes = new_meshes;
}

void Model::draw(){
    for ( Mesh &m : meshes){
        m.draw();
    }
}