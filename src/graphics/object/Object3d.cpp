//
// Created by arunc on 15/10/2024.
//

#include "graphics/object/Object3d.h"


Object3d::Object3d(std::string fileName) {
    mesh = nullptr;
    loadObject(fileName);
    shader = new Shader();
    materials = new std::vector<Material *>();
    shader->use();
    shader->setInt("texture1", 0);
}

Object3d::Object3d() {
    mesh = nullptr;
    shader = new Shader();

    shader->use();
    shader->setInt("texture1", 0);
}

Object3d::~Object3d() {
}

void Object3d::setScene(Scene3d *scene3d) {
    this->scene3d = scene3d;
}

void Object3d::setTexture(std::string texturePath) {
    texture = new Texture(texturePath);
}


void Object3d::loadObject(std::string fileName) {
    if (fileName == "cube") {
        std::vector<float> vertices = {
            // Fața din spate
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

            // Fața din față
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

            // Fața din stânga
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

            // Fața din dreapta
            0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

            // Fața de sus
            -0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,

            // Fața de jos
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f
        };

        std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3, // fața din spate
            4, 5, 6, 4, 6, 7, // fața din față
            8, 9, 10, 8, 10, 11, // fața din stânga
            12, 13, 14, 12, 14, 15, // fața din dreapta
            16, 17, 18, 16, 18, 19, // fața de sus
            20, 21, 22, 20, 22, 23 // fața de jos
        };

        mesh = new Mesh(&vertices, &indices);
    } else {
    }
}

void Object3d::draw() {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, poz);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);


    shader->use();
    texture->active();
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    shader->setMat4("view", scene3d->getView());
    shader->setMat4("projection", scene3d->getProject());

    if (mesh != nullptr) {
        mesh->draw();
    } else {
        for (int i = 0; i < meshs->size(); i++) {
            meshs->at(i)->draw();
        }
    }
}

void Object3d::setAngle(float angle) {
    this->angle = angle;
}

void Object3d::setPosition(float x, float y, float z) {
    this->poz[0] = x;
    this->poz[1] = y;
    this->poz[2] = z;
}

void Object3d::setScale(float x, float y, float z) {
    this->scale[0] = x;
    this->scale[1] = y;
    this->scale[2] = z;
}

float Object3d::getAngle() {
    return angle;
}

glm::vec3 Object3d::getPosition() {
    return poz;
}

glm::vec3 Object3d::getScale() {
    return scale;
}

void Object3d::setMeshNew(std::vector<MeshNEW *> *meshs) {
    this->meshs = meshs;
}
