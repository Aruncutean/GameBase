//
// Created by arunc on 26/10/2024.
//

#include "Minecraft.h"

#include "graphics/object/LoadObject3d.h"

Minecraft::Minecraft() {
    scene = new Scene3d();
    camera = new CameraM();
}

Minecraft::~Minecraft() {
    delete scene;
    delete camera;
    delete map;
}

void Minecraft::init() {
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    scene->setCamera(camera);

    // Object3d *object3d = new Object3d("cube");
    // object3d->setTexture("container.jpg");
    // scene->addObject(object3d);

    Object3d *object3d2 = LoadObject3d().load("test.fbx");
    object3d2->setTexture("container.jpg");

   // object3d2->setMeshNew(LoadObject3d().load("test2.dae"));
    scene->addObject(object3d2);

    // Object3d *object3d3 = new Object3d();
    // object3d3->setTexture("container.jpg");
    // object3d3->setMeshNew(LoadObject3d().load("tree.gltf"));
    // scene->addObject(object3d3);

    // map = new Map();
    // map->init();
}

void Minecraft::start() {
}

void Minecraft::update() {
    currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;


    scene->draw();
    /// map->draw(scene->getProject(),scene->getView());

    Uint32 frameTime = SDL_GetTicks() - currentTime;
    if (frameTime < 1000 / 60) {
        SDL_Delay(1000 / 60 - frameTime);
    }
}


void Minecraft::stop() {
}

void Minecraft::keyPress(const Uint8 *state) {
    camera->pressKey(state, deltaTime);
    if (state[SDL_SCANCODE_ESCAPE]) {
        std::cout << "Space pressed" << std::endl;
    }
}

void Minecraft::mouseHandle(const int x, const int y, const Uint32 *state) {
    camera->mouseHandle(x, y, state);
}
