//
// Created by arunc on 14/11/2024.
//

#include "graphics/object/mesh/Vertex.h"

Vertex::Vertex() {
    vertices = new std::vector<glm::vec3>();
    uvs = new std::vector<glm::vec2>();
    normals = new std::vector<glm::vec3>();
    indices = new std::vector<unsigned int>();
}

Vertex::~Vertex() {
    delete vertices;
    delete uvs;
    delete normals;
    delete indices;
}

void Vertex::addVertex(glm::vec3 vertex) {
    vertices->push_back(vertex);
}

void Vertex::addUV(glm::vec2 uv) {
    uvs->push_back(uv);
}

void Vertex::addNormal(glm::vec3 normal) {
    normals->push_back(normal);
}

void Vertex::addIndices(unsigned int i) {
    indices->push_back(i);
}

std::vector<unsigned int> *Vertex::getIndices() {
    return indices;
}

std::vector<glm::vec3> *Vertex::getVertices() {
    return vertices;
}

std::vector<glm::vec2> *Vertex::getUvs() {
    return uvs;
}

std::vector<glm::vec3> *Vertex::getNormals() {
    return normals;
}
