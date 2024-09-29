//
// Created by arunc on 29/09/2024.
//

#ifndef MYGAME_H
#define MYGAME_H
#include "../game/game.h"
#include "../graphics/shader.h"
#include "../graphics/texture.h"
#include "../graphics/mesh.h"
#include "../graphics/render.h"

class MyGame : public Game{
public:
     void init();
     void start();
     void update();
     void stop();


private:
     Shader *shader;
     Texture *texture;
     Mesh *mesh;
     Render *render;
};



#endif //MYGAME_H
