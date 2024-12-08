#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
public:
    Texture(std::string texturePath = "container.jpg");

    ~Texture();

    void active();

private:
    unsigned int texture1;
};
#endif