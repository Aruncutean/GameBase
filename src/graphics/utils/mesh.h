#pragma once


class Mesh {

public:
	Mesh();

	~Mesh();

	void draw();
private:
	unsigned int VBO, VAO, EBO;
};