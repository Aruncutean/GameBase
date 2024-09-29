//
// Created by arunc on 29/09/2024.
//

#include "myGame.h"

void MyGame::init() {
    shader = new Shader();
    texture = new Texture();
    mesh = new Mesh();
    render = new Render();
    shader->use();
    shader->setInt("texture1", 0);
}

void MyGame::start() {
}

void MyGame::update() {
    render->render(*mesh, *shader, *texture);
}

void MyGame::stop() {
}
