//
// Created by arunc on 29/09/2024.
//

#ifndef MYGAME_H
#define MYGAME_H
#include "game/game.h"
#include "graphics/scene/scene2d.h"
#include <vector>
#include "json.hpp"

class MyGame : public Game {
public:
    MyGame();

    ~MyGame();

    void init();

    void start();

    void update();

    void keyPress(const Uint8* state);
    void mouseHandle(const int x, const int y, const Uint32 *state);
    void stop();

    void reset();

    void addPipes();
private:
    bool isRunning=false;
    Scene2d *scene;
    float speed = 0.5f;
    float delta = 0.0f;
    Uint32 lastTime = 0, currentTime;
    std::vector<Object2d *> *pipes;
    Object2d *obj;
    Object2d *pipe;
};


#endif //MYGAME_H
