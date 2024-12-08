//
// Created by arunc on 27/10/2024.
//

#include "stb_image.h"

#include "Map.h"

#include <glad/glad.h>


Map::Map() {
    shader = new Shader();

    shader->use();
    shader->setInt("texture1", 0);

    texture = new Texture("container.jpg");


    unsigned char *data = stbi_load("map.png",
                                    &width, &height, &nChannels,
                                    0);

    float yScale = 64.0f / 256.0f, yShift = 16.0f; // apply a scale+shift to the height data
    int rez = 1;
    unsigned bytePerPixel = nChannels;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char *pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            // vertex
            vertices.push_back(-height / 2.0f + height * i / (float) height); // vx
            vertices.push_back((int) y * yScale - yShift); // vy
            vertices.push_back(-width / 2.0f + width * j / (float) width); // vz
        }
    }
    std::cout << "Loaded " << vertices.size() / 3 << " vertices" << std::endl;
    stbi_image_free(data);

    for (unsigned i = 0; i < height - 1; i += rez) {
        for (unsigned j = 0; j < width; j += rez) {
            for (unsigned k = 0; k < 2; k++) {
                indices.push_back(j + width * (i + k * rez));
            }
        }
    }

    numStrips = (height - 1) / rez;
    numTrisPerStrip = (width / rez) * 2 - 2;
}

void Map::init() {


    glGenVertexArrays(1, &terrainVAO);
    glBindVertexArray(terrainVAO);

    glGenBuffers(1, &terrainVBO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &terrainIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
}

void Map::draw(glm::mat4 proj, glm::mat4 view) {

    shader->use();

    shader->setMat4("projection", proj);
    shader->setMat4("view", view);


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0,-10.0f,0));
    shader->setMat4("model", model);


    glBindVertexArray(terrainVAO);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for(unsigned strip = 0; strip < numStrips; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   // primitive type
                       numTrisPerStrip+2,   // number of indices to render
                       GL_UNSIGNED_INT,     // index data type
                       (void*)(sizeof(unsigned) * (numTrisPerStrip+2) * strip)); // offset to starting index
    }
}
