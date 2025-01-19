//
// Created by arunc on 14/11/2024.
//

#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Vertex {
public:
    Vertex();

    ~Vertex();

    void addVertex(glm::vec3 vertex);

    void addUV(glm::vec2 uv);

    void addNormal(glm::vec3 normal);

    void addIndices(unsigned int i);

    std::vector<glm::vec3> *getVertices();

    std::vector<glm::vec2> *getUvs();

    std::vector<glm::vec3> *getNormals();

    std::vector<unsigned int> *getIndices();

private:
    std::vector<glm::vec3> *vertices;
    std::vector<glm::vec2> *uvs;
    std::vector<glm::vec3> *normals;
    std::vector<unsigned int> *indices;
};


#endif //VERTEX_H
