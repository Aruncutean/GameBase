//
// Created by arunc on 29/09/2024.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_stdinc.h>


class Game {
public:
    virtual ~Game() = default;

    virtual void init() = 0;

    virtual void start() = 0;

    virtual void update() =0;

    virtual void stop() =0;

    virtual void keyPress(const Uint8 *state) =0;

    virtual void mouseHandle(const int x, const int y, const Uint32 *state) =0;

private:
};


#endif //GAME_H
