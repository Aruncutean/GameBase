//
// Created by arunc on 29/09/2024.
//

#ifndef SCENE2D_H
#define SCENE2D_H

#include <vector>
#include "../object/object2d.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Object2d;

class Scene2d {
public:
    Scene2d();

    ~Scene2d();

    void draw();


    void addObject(Object2d *obj);

    void removeObject(std::string id);

    void addBackground(Object2d *obj);

    glm::mat4 getProject() const { return projection; }
    std::vector<Object2d *> *getBackground() { return background; }

private:
    void drawBackground();

    std::vector<Object2d *> *background;
    std::vector<Object2d *> *objects;
    glm::mat4 projection = glm::mat4(1.0f);
};


#endif //SCENE2D_H
