//
// Created by arunc on 21/10/2024.
//

#include "graphics/utils/Camera.h"

Camera::Camera() {
}

Camera::~Camera() {
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}
