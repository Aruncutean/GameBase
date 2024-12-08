//
// Created by arunc on 26/10/2024.
//

#ifndef MINECRAFT_H
#define MINECRAFT_H

#include "../games/minecraft/include/CameraM.h"
#include "../games/minecraft/include/Map.h"
#include "game/game.h"
#include "graphics/scene/Scene3d.h"

class Minecraft : public Game {
public:
    Minecraft();

    ~Minecraft();

    void init();

    void start();

    void update();

    void stop();

    void keyPress( const Uint8* key);
    void mouseHandle(const int x, const int y, const Uint32 *state);

private:
    Scene3d *scene;
    CameraM *camera;

    Map *map;

private:
    float deltaTime = 0;
    float delta = 0.0f;
    Uint32 lastTime = 0, currentTime;
};


#endif //MINECRAFT_H
