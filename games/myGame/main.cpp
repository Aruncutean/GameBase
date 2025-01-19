#include "../../lib/SDL/include/SDL.h"
#include "../minecraft/include/Minecraft.h"
#include "myGame.h"
#include "../../include/window/window.h"


int main(int argc, char* argv[]) {

   // Game *game=new MyGame();
    Game *game=new Minecraft();
    Window *window=new Window(game);

    window->init();

    window->start();
    window->stop();

    return 0;
}
