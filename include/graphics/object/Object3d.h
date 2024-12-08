//
// Created by arunc on 15/10/2024.
//

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <graphics/utils/mesh.h>

#include "graphics/utils/shader.h"
#include "graphics/utils/texture.h"
#include "graphics/object/Object3d.h"
#include "graphics/scene/Scene3d.h"
#include "mesh/Mesh.h"
#include "graphics/material/Material.h"

class Scene3d;

class Object3d {
public:
    Object3d(std::string fileName);

    Object3d();

    ~Object3d();

    void setScene(Scene3d *scene3d);

    void loadObject(std::string fileName);

    void draw();

    void setTexture(std::string texturePath);

    void setMaterial(std::vector<Material *> *materials) { this->materials = materials; }

    void setAngle(float angle);

    void setPosition(float x, float y, float z);

    void setScale(float x, float y, float z);

    float getAngle();

    glm::vec3 getPosition();

    glm::vec3 getScale();

    void setMeshNew(std::vector<MeshNEW *> *meshs);

private:
    Shader *shader;
    Texture *texture;
    Mesh *mesh;
    std::vector<MeshNEW *> *meshs;

    Scene3d *scene3d;

    std::vector<Material *> *materials;

    float angle = 0;
    glm::vec3 poz = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};


#endif //OBJECT3D_H
