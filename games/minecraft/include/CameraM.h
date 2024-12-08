//
// Created by arunc on 27/10/2024.
//

#ifndef CAMERAM_H
#define CAMERAM_H

#include <SDL_stdinc.h>

#include "graphics/utils/Camera.h"

class CameraM : public Camera {
public:
    CameraM();

    void pressKey(const  Uint8 *state,float deltaTime);

    void mouseHandle(const int x, const int y, const Uint32 *state);
private:
    float yaw   = -90.0f;
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  45.0f;
    bool firstMouse = true;
};


#endif //CAMERAM_H
