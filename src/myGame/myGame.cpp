//
// Created by arunc on 29/09/2024.
//

#include "myGame.h"

#include "../graphics/scene/scene2d.h"

MyGame::MyGame() {
}

MyGame::~MyGame() {
    delete scene;
}

void MyGame::init() {
    scene = new Scene2d();

    Object2d *obj = new Object2d();
    obj->setTexture("bird.png");
    obj->setScale(125.0f / 2, 126.0f / 2);

    Object2d *bg = new Object2d();
    bg->setTexture("bg.jpeg");
    bg->setScale(284.0f, 512.0f);

    Object2d *bg1 = new Object2d(*bg);
    Object2d *bg2 = new Object2d(*bg);
    Object2d *bg3 = new Object2d(*bg);
    Object2d *bg4 = new Object2d(*bg);
    Object2d *bg5 = new Object2d(*bg);
    scene->addObject(obj);
    scene->addBackground(bg);
    scene->addBackground(bg1);
    scene->addBackground(bg2);
    scene->addBackground(bg3);
    scene->addBackground(bg4);
    scene->addBackground(bg5);
}

void MyGame::start() {
    for (int i = 0; i < scene->getBackground()->size(); i++) {
        scene->getBackground()->at(i)->setPoz(i*283.0f,300.0f);
    }
}

void MyGame::update() {
    for (int i = 0; i < scene->getBackground()->size(); i++) {
        scene->getBackground()->at(i)->setPoz(scene->getBackground()->at(i)->getPoz().x - speed * 0.09f,300.0f);

        if ( scene->getBackground()->at(i)->getPoz().x < -283.0f) {
            scene->getBackground()->at(i)->setPoz(5*283.0f,300.0f);
        }

    }

    scene->draw();
}

void MyGame::stop() {
}
