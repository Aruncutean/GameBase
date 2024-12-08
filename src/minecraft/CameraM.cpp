//
// Created by arunc on 27/10/2024.
//

#include "CameraM.h"

#include <iostream>
#include <ostream>

#include "SDL.h"

CameraM::CameraM() {
}

void CameraM::pressKey(const Uint8 *state, float deltaTime) {
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (state[SDL_SCANCODE_W]) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (state[SDL_SCANCODE_A]) {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (state[SDL_SCANCODE_S]) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (state[SDL_SCANCODE_D]) {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
}

void CameraM::mouseHandle(const int x, const int y, const Uint32 *state) {
    float xpos = static_cast<float>(x);
    float ypos = static_cast<float>(y);
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (*state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(front);
    }
}
