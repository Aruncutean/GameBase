#pragma once


class Mesh {

public:
	Mesh();

	~Mesh();

	void render();
private:
	unsigned int VBO, VAO, EBO;
};