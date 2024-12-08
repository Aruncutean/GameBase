//
// Created by arunc on 15/10/2024.
//

#ifndef SCENE3D_H
#define SCENE3D_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "graphics/object/Object3d.h"
#include "graphics/utils/Camera.h"

class Object3d;

class Scene3d {
public:
    Scene3d();

    ~Scene3d();

    void draw();

    void addObject(Object3d *obj);
    void setCamera(Camera *camera);
    glm::mat4 getProject();
    glm::mat4 getView();
private:
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    std::vector<Object3d *> *objects;

    Camera *camera;
};


#endif //SCENE3D_H
