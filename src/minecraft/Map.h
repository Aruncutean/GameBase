//
// Created by arunc on 27/10/2024.
//

#ifndef MAP_H
#define MAP_H
#include <vector>

#include "graphics/utils/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "setting/Setting.h"
#include "graphics/utils/texture.h"

const int CHUNK_SIZE = 4;

struct Block {
    bool isSolid;
};

class Map {
public:
    Map();

    void init();

    void draw(glm::mat4 proj, glm::mat4 view);

private:

    std::vector<float> vertices; // Vârfurile pentru mesh
    std::vector<int> indices;

    Shader *shader;
    Texture *texture;

    GLuint VBO, EBO;
    unsigned int terrainVAO, terrainVBO, terrainIBO;
    int width, height, nChannels;
     int numStrips;
     int numTrisPerStrip ;
};


#endif //MAP_H
