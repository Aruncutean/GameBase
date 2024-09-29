#pragma once

#include "mesh.h"
#include "shader.h"
#include "texture.h"

class Render {

public:
	Render();

	~Render();


	void render(Mesh mesh, Shader shader, Texture texture);
private:

};