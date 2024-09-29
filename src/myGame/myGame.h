//
// Created by arunc on 29/09/2024.
//

#ifndef MYGAME_H
#define MYGAME_H
#include "../game/game.h"
#include "../graphics/scene/scene2d.h"
#include <vector>
class MyGame : public Game {
public:
    MyGame();
    ~MyGame();

    void init();

    void start();

    void update();

    void stop();

private:
    Scene2d *scene;
    float speed = 0.5f;
    std::vector<Object2d *> *pipes;
    Object2d *pipe;
};


#endif //MYGAME_H
