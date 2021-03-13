#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <model.h>

#include <iostream>

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
                          (void *)offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);
    // // color (r, g, b) location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(struct Vertex, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Model::set_meshes(std::vector<Mesh> new_meshes) { meshes = new_meshes; }

void Model::draw() {
    for (Mesh &m : meshes) {
        m.draw();
    }
}

void Model::load_model(std::string path) {
    Assimp::Importer importer;
    const aiScene *scene =
        importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cout << "assimp import error: " << importer.GetErrorString()
                  << "\n";
        return;
    }
    std::string dir = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        process_node(node->mChildren[i], scene);
    }
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                                mesh->mVertices[i].z),
                      glm::vec3(1.0, 0.0, 0.0));
        vertices.push_back(vertex);
    }

    return Mesh(vertices);
}