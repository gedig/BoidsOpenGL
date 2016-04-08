#ifndef INCLUDE_GRID_HPP
#define INCLUDE_GRID_HPP

#pragma once

#include "ShaderProgram.hpp"

#include <string>

#include <SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Grid {
public:
	Grid();
	~Grid();

	void Init();
	void Render(glm::mat4 viewProjection);

	GLfloat GetFieldSize() { return numVertices / 2.0f * lineDistance; }

private:
	ShaderProgram shader;
	GLuint vbo[1], vao[1];
	GLuint vertexAttribIndex;
	int numVertices;
	float lineDistance;
};

#endif // !INCLUDE_GRID_HPP