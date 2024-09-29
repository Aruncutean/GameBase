#pragma once
#include <string>

class Texture {
public:
    Texture(std::string texturePath = "container.jpg");

    ~Texture();

    void active();

private:
    unsigned int texture1;
};
