//
// Created by arunc on 29/09/2024.
//

#include "scene2d.h"

Scene2d::Scene2d() {
    objects = new std::vector<Object2d *>;
    background=new std::vector<Object2d *>;

}

Scene2d::~Scene2d() {
}



void Scene2d::draw() {
    projection = glm::ortho(0.0f, 800.0f,  600.0f,0.0f);
    drawBackground();
    for (int i = 0; i < objects->size(); i++) {
        objects->at(i)->draw();
    }
}

void Scene2d::drawBackground() {
    if( background && background->size()>0) {
        for (int i = 0; i < background->size(); i++) {
            background->at(i)->draw();
        }
    }
}

void Scene2d::addObject(Object2d *obj) {
    obj->setScene(this);
    objects->push_back(obj);
}

void Scene2d::removeObject(std::string id) {
    objects->erase(std::remove_if(objects->begin(), objects->end(), [id](Object2d* i) { return i->id == id; }), objects->end());
}

void Scene2d::addBackground(Object2d *obj) {
    obj->setScene(this);
    background->push_back(obj);
}


