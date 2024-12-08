//
// Created by arunc on 15/10/2024.
//

#include "graphics/scene/Scene3d.h"

Scene3d::Scene3d() {
    objects = new std::vector<Object3d *>;
}

Scene3d::~Scene3d() {
}

void Scene3d::draw() {
    projection = glm::perspective(glm::radians(60.0f), (float) 800 / (float) 512, 0.1f, 100.0f);
    view = camera->getViewMatrix();
    for (int i = 0; i < objects->size(); i++) {
        objects->at(i)->draw();
    }
}

void Scene3d::addObject(Object3d *obj) {
    objects->push_back(obj);
    obj->setScene(this);
}

void Scene3d::setCamera(Camera *camera) {
    this->camera = camera;
}

glm::mat4 Scene3d::getProject() {
    return projection;
}

glm::mat4 Scene3d::getView() {
    return view;
}
