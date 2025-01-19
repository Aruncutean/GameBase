//
// Created by arunc on 14/11/2024.
//

#ifndef LOADOBJECT3D_H
#define LOADOBJECT3D_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "mesh/Mesh.h"
#include "mesh/Vertex.h"
#include <fbxsdk.h>
#include "Object3d.h"

class LoadObject3d {
public:
    LoadObject3d();

    ~LoadObject3d();

    static Object3d *load(std::string path);
    static void LoadUVInformation(FbxMesh* pMesh,Vertex *vertex);
private:

};


#endif //LOADOBJECT3D_H
