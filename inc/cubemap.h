#pragma once
#include <string>
#include <vector>

class CubeMap {
    unsigned int id, vao, vbo;

   public:
    CubeMap(std::vector<std::string> face_paths);
    unsigned int get_id();
    unsigned int get_vao();
    unsigned int get_vbo();
    void draw();
};

