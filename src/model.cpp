#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <model.h>
#include <texture.h>
#include <util.h>

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures)
    : vertices(vertices), textures(textures) {
    setup_mesh();
}

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
    // // normal (x, y, z) location = 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(struct Vertex, normal));
    glEnableVertexAttribArray(1);

    // // texture coordinates (x, y) location = 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(struct Vertex, texture));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader) {
    for (unsigned int i = 0; i < textures.size(); i++) {
        switch (textures[i].type) {
            case TextureType::Diffuse:
                shader.set_int("material.diffuse", i);
                break;
            case TextureType::Specular:
                shader.set_int("material.specular", i);
                break;
        }
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);

    // Reset textures
    shader.set_int("material.diffuse", 0);
    shader.set_int("material.specular", 0);
    glActiveTexture(GL_TEXTURE0);
}

void Model::set_meshes(std::vector<Mesh> new_meshes) { meshes = new_meshes; }

void Model::draw(Shader &shader) {
    for (Mesh &m : meshes) {
        m.draw(shader);
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

std::vector<Texture> Model::load_textures(aiMaterial *mat,
                                          aiTextureType tex_type) {
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(tex_type); i++) {
        aiString str;
        mat->GetTexture(tex_type, i, &str);
        bool cached = false;
        for (Texture &t : texture_cache) {
            aiString p;
            p = get_exe_path();
            p.Append("/env/");
            p.Append(str.C_Str());
            if (strcmp(t.path.c_str(), p.C_Str()) == 0) {
                textures.push_back(t);
                cached = true;
                break;
            }
        };
        if (!cached) {
            Texture texture(get_exe_path() + std::string("/env/") +
                                std::string(str.C_Str()),
                            aitex_to_ourtex(tex_type));
            textures.push_back(texture);
            texture_cache.push_back(texture);
        }
    }
    return textures;
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                               mesh->mVertices[i].z);
        if (mesh->HasNormals())
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                                      mesh->mNormals[i].z);
        if (mesh->HasTextureCoords(0)) {
            vertex.texture = glm::vec2(mesh->mTextureCoords[0][i].x,
                                       mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texture = glm::vec2(0.0, 0.0);
        }

        vertices.push_back(vertex);

        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuse_textures =
            load_textures(mat, aiTextureType_DIFFUSE);
        textures.insert(textures.end(), diffuse_textures.begin(),
                        diffuse_textures.end());

        std::vector<Texture> specular_textures =
            load_textures(mat, aiTextureType_SPECULAR);
        textures.insert(textures.end(), specular_textures.begin(),
                        specular_textures.end());
    }

    return Mesh(vertices, textures);
}