#include "SDL.h"
#include "myGame/myGame.h"
#include "window/window.h"


int main(int argc, char* argv[]) {

    Game *game=new MyGame();
    Window *window=new Window(game);

    window->init();

    window->start();
    window->stop();

    return 0;
}
