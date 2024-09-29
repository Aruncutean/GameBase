#include "texture.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <SDL.h>
#include <string>
#include <vector>
Texture::Texture(std::string texturePath)
{
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_RWops* file = SDL_RWFromFile(texturePath.c_str(), "rb");
    if (!file) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to open file from assets: %s", SDL_GetError());
        return;
    }

    Sint64 fileSize = SDL_RWsize(file);
    if (fileSize <= 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "File size error: %s", SDL_GetError());
        SDL_RWclose(file);
        return;
    }

    std::vector<unsigned char> buffer(fileSize);
    Sint64 bytesRead = SDL_RWread(file, buffer.data(), 1, fileSize);
    SDL_RWclose(file);

    if (bytesRead != fileSize) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to read the full file: %s", SDL_GetError());
        return;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load_from_memory(buffer.data(), buffer.size(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        // Textura este încărcată corect
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        SDL_Log("Image loaded successfully");
    } else {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture with stb_image: %s", stbi_failure_reason());
    }

    stbi_image_free(data);

}

Texture::~Texture()
{
}

void Texture::active()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
}
