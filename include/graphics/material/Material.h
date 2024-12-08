//
// Created by arunc on 14/11/2024.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material {
public:
    Material();

    ~Material();

    void setTexture(Texture *texture) { this->texture = texture; }
    Texture *getTexture() { return this->texture; }

    void setName(std::string name) { this->name = name; }
    std::string getName() { return this->name; }

    void setBaseColor(glm::vec4 color) { this->baseColor = color; }
    glm::vec4 getBaseColor() { return this->baseColor; }

    void setMetallic(double metallic) { this->metallic = metallic; }
    double getMetallic() { return this->metallic; }

    void setRoughness(double roughness) { this->roughness = roughness; }
    double getRoughness() { return this->roughness; }

    void setIor(double ambient) { this->ior = ior; }
    double getIor() { return this->ior; }

    void setAlpha(double alpha) { this->alpha = alpha; }
    double getAlpha() { return this->alpha; }

private:
    Texture *texture;

    std::string name;
    glm::vec4 baseColor;
    double metallic;
    double roughness;
    double ior;
    double alpha;
};


#endif //MATERIAL_H
