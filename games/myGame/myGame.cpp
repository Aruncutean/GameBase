//
// Created by arunc on 29/09/2024.
//

#include "myGame.h"

#include "graphics/scene/scene2d.h"
#include <fstream>
#include <iostream>

MyGame::MyGame() {
    std::ifstream fJson("test.json");
    std::stringstream buffer;
    buffer << fJson.rdbuf();
    auto json = nlohmann::json::parse(buffer.str());
}

MyGame::~MyGame() {
    delete scene;
}

void MyGame::init() {
    scene = new Scene2d();
    pipes = new std::vector<Object2d *>;

    obj = new Object2d();
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
    this->addPipes();
}

void MyGame::update() {
    if (isRunning) {
        for (int i = 0; i < scene->getBackground()->size(); i++) {
            scene->getBackground()->at(i)->setPoz(scene->getBackground()->at(i)->getPoz().x - speed * 0.09f, 300.0f);

            if (scene->getBackground()->at(i)->getPoz().x < -283.0f) {
                scene->getBackground()->at(i)->setPoz(5 * 283.0f, 300.0f);
            }
        }


        for (int i = 0; i < pipes->size(); i++) {
            pipes->at(i)->setPoz(pipes->at(i)->getPoz().x - speed * 0.09f, pipes->at(i)->getPoz().y);
        }

        if (pipes->size() > 0 && pipes->back()->getPoz().x <= 800 - 100) {
            this->addPipes();
        }

        if (pipes->size() > 0 && pipes->front()->getPoz().x < -200) {
            scene->removeObject(pipes->at(0)->id);
            scene->removeObject(pipes->at(1)->id);
            delete pipes->at(0);
            delete pipes->at(1);
            pipes->erase(pipes->begin(), pipes->begin() + 2);
        }

        if (pipes->size() > 0) {
            for (int i = 0; i < pipes->size(); i++) {
                bool collisionX = obj->getPoz().x - obj->getScale().x / 2 < pipes->at(i)->getPoz().x + pipes->at(i)->
                                  getScale().x / 2 &&
                                  obj->getPoz().x + obj->getScale().x / 2 > pipes->at(i)->getPoz().x - pipes->at(i)->
                                  getScale().x / 2;

                bool collisionY = obj->getPoz().y - obj->getScale().y / 2 < pipes->at(i)->getPoz().y + pipes->at(i)->
                                  getScale().y / 2 &&
                                  obj->getPoz().y + obj->getScale().y / 2 > pipes->at(i)->getPoz().y - pipes->at(i)->
                                  getScale().y / 2;


                float closestX = fmax(pipes->at(i)->getPoz().x - pipes->at(i)->getScale().x / 2,
                                      fmin(obj->getPoz().x, pipes->at(i)->getPoz().x + pipes->at(i)->getScale().x / 2));
                float closestY = fmax(pipes->at(i)->getPoz().y - pipes->at(i)->getScale().y / 2,
                                      fmin(obj->getPoz().y, pipes->at(i)->getPoz().y + pipes->at(i)->getScale().y / 2));

                // Calculează distanța dintre centrul cercului și acest punct
                float dx = obj->getPoz().x - closestX;
                float dy = obj->getPoz().y - closestY;
                float radius = 22.0f;
                if ((dx * dx + dy * dy) < (radius * radius)) {
                    std::cout << pipes->at(i)->id << std::endl;
                    isRunning = false;
                    //     std::cout << pipes->at(i)->id << std::endl;
                    this->reset();
                    break;
                }


                // if (collisionY && collisionX) {
                //     isRunning = false;
                //     std::cout << pipes->at(i)->id << std::endl;
                //     // this->reset();
                //     break;
                // }
            }
        }
        currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        delta += 0.15f;
        obj->setAngle(delta / 10.0f);
        obj->setPoz(obj->getPoz().x, obj->getPoz().y + delta * deltaTime);

        //   std::cout << obj->getPoz().x << " " << obj->getPoz().y << std::endl;
        if (obj->getPoz().y < 0 || obj->getPoz().y > 520) {
            isRunning = false;
            this->reset();
        }
    }
    scene->draw();

    Uint32 frameTime = SDL_GetTicks() - currentTime;
    if (frameTime < 1000 / 120) {
        SDL_Delay( 1000 / 120 - frameTime);
    }
}

void MyGame::keyPress(const  Uint8* state) {
    if (state[SDL_SCANCODE_SPACE]) {
        if (isRunning) {
            delta = -100.0f;
            obj->setAngle(-40);
        }
        if (!isRunning) {
            isRunning = true;
        }
    }
}

void MyGame::mouseHandle(const int x, const int y, const Uint32 *state) {
}

void MyGame::stop() {
}

void MyGame::reset() {

    std::cout << pipes->size() << std::endl;
    for (int i = 0; i < pipes->size(); i++) {
        scene->removeObject(pipes->at(i)->id);
        if (pipes->at(i) != nullptr) { delete pipes->at(i); }
    }
    pipes->clear();
    std::cout << pipes->size() << std::endl;
    this->addPipes();

    obj->setPoz(400, 300);
    obj->setAngle(0);
}

void MyGame::addPipes() {
    float randomOffset = static_cast<float>(rand() % static_cast<int>(100.0f * 2)) - 100.0f;
    Object2d *pipeUp = new Object2d(*pipe);
    pipeUp->setPoz(900.0f, 80.0f + randomOffset);
    pipeUp->setAngle(180);
    Object2d *pipeDown = new Object2d(*pipe);
    pipeDown->setPoz(900.0f, 525.0f + randomOffset);
    pipes->push_back(pipeUp);
    pipes->push_back(pipeDown);

    scene->addObject(pipeUp);
    scene->addObject(pipeDown);
}
