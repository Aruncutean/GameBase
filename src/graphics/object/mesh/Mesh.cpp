//
// Created by arunc on 14/11/2024.
//

#include "graphics/object/mesh/Mesh.h"
#include "setting/Setting.h"
#include <glad/glad.h>

MeshNEW::MeshNEW(Vertex *vertices) {
    this->vertices = vertices;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBOVertices);
    glGenBuffers(1, &VBONormal);
    glGenBuffers(1, &VBOUvs);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBOVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices->getVertices()->size() *  sizeof(glm::vec3), vertices->getVertices()->data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBONormal);
    glBufferData(GL_ARRAY_BUFFER, vertices->getNormals()->size() * sizeof(glm::vec3), vertices->getNormals()->data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VBOUvs);
    glBufferData(GL_ARRAY_BUFFER, vertices->getUvs()->size() * sizeof(glm::vec2), vertices->getUvs()->data(),
                 GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertices->getIndices()->size() * sizeof(unsigned int),
                 vertices->getIndices()->data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MeshNEW::~MeshNEW() {
    delete vertices;
}


void MeshNEW::draw() {
    glBindVertexArray(VAO);
    if (Setting::getInstance().enableLineRender) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glDrawElements(GL_TRIANGLES, vertices->getIndices()->size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
