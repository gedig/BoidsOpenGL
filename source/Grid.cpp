#include "Grid.hpp"

#include <iostream>

Grid::Grid() : numVertices(100), lineDistance(3.0f), vertexAttribIndex(0)
{
}

Grid::~Grid()
{
	glDeleteVertexArrays(1, vao);
	glDeleteBuffers(1, vbo);
}

void Grid::Init() {
	std::cout << gluErrorString(glGetError()) << std::endl;
	if (!shader.Init("grid")) {
		// TODO-DG: Handle error gracefully
	}
	
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	
	float lineLength = numVertices * lineDistance;
	glm::vec3 *vertices = new glm::vec3[numVertices];

	for (int i = 0; i < numVertices; i+=4) {
		vertices[i] = glm::vec3(lineDistance * (i - numVertices/2), 0.0f, -lineLength/2.0f);
		vertices[i+1] = glm::vec3(lineDistance * (i - numVertices / 2), 0.0f, lineLength / 2.0f);
		vertices[i+2] = glm::vec3(-lineLength/2.0f, 0.0f, lineDistance * (i - numVertices / 2));
		vertices[i+3] = glm::vec3(lineLength/2.0f, 0.0f, lineDistance * (i - numVertices / 2));
	}

	/* Used for printing vertices because the Visual Studio inspector doesn't like arrays of glm data types
	for (int i = 0; i < numVertices; i++) {
		std::cout << vertices[i].x << ", " << vertices[i].y << ", " << vertices[i].z << std::endl;
	}*/
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numVertices, vertices, GL_STATIC_DRAW);
	std::cout << gluErrorString(glGetError()) << std::endl;
	glVertexAttribPointer(vertexAttribIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttribIndex);

	delete[] vertices;
}

void Grid::Render(glm::mat4 viewProjection)
{
	glBindVertexArray(vao[0]);
	glEnableVertexAttribArray(vertexAttribIndex);
	glm::mat4 mvp = viewProjection * glm::mat4();
	shader.UseProgram();
	shader.SetMatrix(mvp);
	shader.SetColour(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	glDrawArrays(GL_LINES, 0, numVertices);
	glDisableVertexAttribArray(vertexAttribIndex);
	shader.StopProgram();
}
