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
    pipes = new std::vector<Object2d *>;

    Object2d *obj = new Object2d();
    obj->setTexture("bird.png");
    obj->setScale(125.0f / 2, 126.0f / 2);

    pipe = new Object2d();
    pipe->setTexture("pipe.png");
    pipe->setScale(52.0f, 320.0f);

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
        scene->getBackground()->at(i)->setPoz(i * 283.0f, 300.0f);
    }
    float randomOffset = static_cast<float>(rand() % static_cast<int>(100.0f * 2)) - 100.0f;
    Object2d *pipeUp = new Object2d(*pipe);
    pipeUp->setPoz(900.0f, 80.0f +randomOffset);
    pipeUp->setAngle(180);
    Object2d *pipeDown = new Object2d(*pipe);
    pipeDown->setPoz(900.0f, 500.0f +randomOffset);
    pipes->push_back(pipeUp);
    pipes->push_back(pipeDown);

    scene->addObject(pipeUp);
    scene->addObject(pipeDown);
}

void MyGame::update() {
    for (int i = 0; i < scene->getBackground()->size(); i++) {
        scene->getBackground()->at(i)->setPoz(scene->getBackground()->at(i)->getPoz().x - speed * 0.09f, 300.0f);

        if (scene->getBackground()->at(i)->getPoz().x < -283.0f) {
            scene->getBackground()->at(i)->setPoz(5 * 283.0f, 300.0f);
        }
    }


    for (int i = 0; i < pipes->size(); i++) {
        pipes->at(i)->setPoz(pipes->at(i)->getPoz().x - speed * 0.09f, pipes->at(i)->getPoz().y);
    }

    if (pipes->size()>0 && pipes->back()->getPoz().x <= 800-100) {

        float randomOffset = static_cast<float>(rand() % static_cast<int>(100.0f * 2)) - 100.0f;
        Object2d *pipeUp = new Object2d(*pipe);
        pipeUp->setPoz(900.0f, 80.0f+randomOffset);
        pipeUp->setAngle(180);
        Object2d *pipeDown = new Object2d(*pipe);
        pipeDown->setPoz(900.0f, 500.0f+randomOffset);
        pipes->push_back(pipeUp);
        pipes->push_back(pipeDown);

        scene->addObject(pipeUp);
        scene->addObject(pipeDown);
    }

    if (pipes->size()>0 && pipes->front()->getPoz().x < -200) {
        scene->removeObject(pipes->at(0)->id);
        scene->removeObject(pipes->at(1)->id);
        delete pipes->at(0);
        delete pipes->at(1);
        pipes->erase(pipes->begin(), pipes->begin() + 2);
    }

    scene->draw();
}

void MyGame::stop() {
}
