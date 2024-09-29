//
// Created by arunc on 29/09/2024.
//

#include "object2d.h"
#include "../../utils/utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object2d::Object2d() {
    id = Utils::generateUniqueID();
    mesh = new Mesh();

    shader = new Shader();

    shader->use();
    shader->setInt("texture1", 0);
}

Object2d::Object2d(Object2d &object2d) {
    id = Utils::generateUniqueID();
    mesh = object2d.mesh;
    shader = object2d.shader;
    texture = object2d.texture;
    scene2d = object2d.scene2d;
    poz = object2d.poz;
    scale = object2d.scale;
}

Object2d::~Object2d() {
}

void Object2d::setTexture(std::string texturePath) {
    texture = new Texture(texturePath);
}

void Object2d::setScene(Scene2d *scene) {
    this->scene2d = scene;
}

void Object2d::draw() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    model = glm::translate(model, poz);
    model = glm::scale(model, scale);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    shader->use();
    texture->active();
    unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
    unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    shader->setMat4("projection", scene2d->getProject());


    mesh->draw();
}

void Object2d::setPoz(float x, float y) {
    this->poz.x = x;
    this->poz.y = y;
}

void Object2d::setScale(float x, float y) {
    this->scale.x = x;
    this->scale.y = y;
}
