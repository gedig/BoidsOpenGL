#ifndef INCLUDE_SHADERPROGRAM_HPP
#define INCLUDE_SHADERPROGRAM_HPP

#pragma once

#define POSSIBLE_SHADERS 4 // Vertex, Tesselation, Geometry, and Fragment. Will need to increase this if compute shaders are implemented.

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ShaderPaths.hpp"

// Class that encapsulates a Shader Program, handling all of the openGL communication.
class ShaderProgram {
public:
	ShaderProgram();
	ShaderProgram(std::string shaderName, bool &failure, bool geometry = false);
	~ShaderProgram();

	GLuint getID() { return programID; }
	int Init(std::string shaderName, bool geometry = false);
	void UseProgram() const { glUseProgram(programID); }
	void StopProgram() const { glUseProgram(0); }
	bool LoadShader(const std::string &filename, GLenum shaderType);
	void SetColour(const glm::vec4 colour);
	void SetMatrix(glm::mat4 mat);

private:

	bool TryCompileShader(int shaderID);
	int CreateShader(const std::string &filename, GLenum shaderType);
	bool LinkShaders();
	void PrintShaderLinkingError(int32_t shaderID);

	void PrintShaderCompilationErrorInfo(int32_t shaderID);

	std::string ReadFile(const char* file);

	// Handle to the shader program
	GLuint programID;

	GLuint colourID;
	bool colourIDSet;
	GLuint matrixID;
	bool matrixIDSet;
	
	int currentShaders;
	int shaderIDs[POSSIBLE_SHADERS];
};

#endif