//
// Created by arunc on 14/11/2024.
//

#ifndef MESH_H
#define MESH_H
#include "Vertex.h"

class MeshNEW {
public:
    MeshNEW(Vertex *vertices);

    ~MeshNEW();

    void draw();

private:
    Vertex *vertices;

    unsigned int VAO, EBO;
    unsigned int VBOVertices;
    unsigned int VBONormal;
    unsigned int VBOUvs;
};


#endif //MESH_H
