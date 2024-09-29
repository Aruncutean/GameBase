//
// Created by arunc on 29/09/2024.
//

#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <iostream>

#include "../scene/scene2d.h"
#include "../utils/shader.h"
#include "../utils/texture.h"
#include "../utils/mesh.h"

class Scene2d;

class Object2d {
public:
    std::string id;
    Object2d();

    Object2d(Object2d &object2d);

    ~Object2d();

    void setTexture(std::string texturePath);

    void setScene(Scene2d *scene);

    void draw();

    void setPoz(float x, float y);

    void setAngle(float angle) {
        this->angle = angle;
    }

    glm::vec3 getPoz() { return poz; }

    void setScale(float x, float y);

private:


    Scene2d *scene2d;
    Shader *shader;
    Texture *texture;
    Mesh *mesh;
    float angle = 0;
    glm::vec3 poz = glm::vec3(400.0f, 300.0f, 0.0f);
    glm::vec3 scale = glm::vec3(100.0f, 100.0f, 1.0f);
};
#endif //OBJECT2D_H
