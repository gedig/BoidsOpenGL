#ifndef INCLUDE_MODEL_HPP
#define INCLUDE_MODEL_HPP

#pragma once

#include <ShaderProgram.hpp>

#include <string>
#include<vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
* Class to keep track of the model and shader information needed to render something.
*/
class Model {
public:
	Model();
	~Model();

	int Init(std::string modelName);

	void SetMatrix(glm::mat4 mvp);
	void SetShader(ShaderProgram _shader) { shader = _shader; }
	void Render() const;
private:
	bool SetupBufferObjects(std::string modelName);
	static std::vector<GLfloat> Model::ReadFile(const char* file) {
		// Open file
		std::ifstream t(file);

		std::vector<GLfloat> result;
		std::cout << "Reading : " << file << std::endl;

		while (t.good())
		{
			std::string str;
			t >> str;

			GLfloat f = std::atof(str.c_str());

			result.push_back(f);
		}

		return result;
	}
	std::vector<GLfloat> positions;
	std::vector<GLfloat> colours;

	GLuint vbo[2], vao[1];

	const uint32_t positionAttributeIndex, colourAttributeIndex;

	ShaderProgram shader;
};

#endif