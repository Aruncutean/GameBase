#include "graphics/utils/texture.h"
#include <glad/glad.h>

#include <SDL.h>
#include <string>
#include <vector>

#include "SDL_image.h"

Texture::Texture(std::string texturePath) {
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_Surface *surface = IMG_Load(texturePath.c_str());

    if (surface) {
        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     format,
                     surface->w,
                     surface->h,
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

        SDL_Log("Image loaded successfully");
    }
    SDL_FreeSurface(surface);
}

Texture::~Texture() {
}

void Texture::active() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
}
