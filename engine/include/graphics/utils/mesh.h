#pragma once

#include <vector>
#include "setting/Setting.h"
class Mesh {
public:
    Mesh(std::vector<float> *vertices, std::vector<unsigned int> *indices);

    ~Mesh();

    void draw();

private:
    unsigned int sizeIndex = 0;
    unsigned int VBO, VAO, EBO;
};
