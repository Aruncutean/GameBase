//
// Created by arunc on 29/09/2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "glad/glad.h"
#include <iostream>

#include "../game/game.h"

class Window {
public:
    Window(Game *game);

    ~Window();

    void init();

    void start();

    void stop();

private:
    SDL_Window *window;
    SDL_GLContext gl_context;
    bool running = true;
    Game *game;

    void initSDL();

    void loop();

    void createContext();
};


#endif //WINDOW_H
