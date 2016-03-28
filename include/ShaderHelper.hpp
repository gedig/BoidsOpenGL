#ifndef INCLUDE_SHADERHELPER_HPP
#define INCLUDE_SHADERHELPER_HPP

#pragma once

#include <GL/glew.h>
#include <SDL.h>

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ShaderPaths.hpp"

class ShaderHelper {
public:

	void UseProgram() {
		glUseProgram(shaderProgram);
	}

	bool Init(std::string shaderName, bool geometry = false) {
		shaderProgram = glCreateProgram();
		
		std::string shaderPath = generated::ShaderPaths::getShaderDirectory();
		if (!LoadShader(shaderPath + shaderName + ".vs.glsl", GL_VERTEX_SHADER))
			return false;

		if (!LoadShader(shaderPath + shaderName + ".fs.glsl", GL_FRAGMENT_SHADER))
			return false;

		// Geometry shader is optional
		if (geometry) {
			if (!LoadShader(shaderPath + shaderName + ".gs.glsl", GL_GEOMETRY_SHADER))
				return false;
		}

		return LinkShaders();
	}

	bool LoadShader(const std::string &filename, GLenum shaderType) {
		std::cout << "Loading Shader: " << filename << std::endl;

		int shaderID = CreateShader(filename, shaderType);

		if (TryCompileShader(shaderID)) {
			glAttachShader(shaderProgram, shaderID);
			shaderIDs.push_back(shaderID);

			return true;
		}

		return false;
	}

	void CleanUp() {
		glUseProgram(0);
		for (auto i : shaderIDs)
			glDetachShader(shaderProgram, i);

		glDeleteProgram(shaderProgram);

		for (auto i : shaderIDs)
			glDeleteShader(i);
	}

private:

	bool TryCompileShader(int shaderID) {
		glCompileShader(shaderID);

		int compiled = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);

		if (compiled == false)
			PrintShaderCompilationErrorInfo(shaderID);

		return (compiled != 0);
	}

	int CreateShader(const std::string &filename, GLenum shaderType) {

		std::string str = ReadFile(filename.c_str());

		char* src = const_cast<char*>(str.c_str());
		int32_t size = str.length();

		int shaderID = glCreateShader(shaderType);

		glShaderSource(shaderID, 1, &src, &size);

		return shaderID;
	}

	bool LinkShaders() {
		glLinkProgram(shaderProgram);

		int linked = 0;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *)&linked);
		if (linked == false)
			PrintShaderLinkingError(shaderProgram);

		return linked != 0;
	}

	void PrintShaderLinkingError(int32_t shaderID) {
		std::cout << "===============================\n";
		std::cout << "Shader linking failed: " << std::endl;

		int maxLength = 0;
		glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::cout << "Info Length : " << maxLength << std::endl;

		char* shaderProgramInfoLog = new char[maxLength];
		glGetProgramInfoLog(shaderProgram, maxLength, &maxLength, shaderProgramInfoLog);

		std::cout << "Linker error message: " << shaderProgramInfoLog << std::endl;

		// Can handle the error differently here, like printing to a file or displaying a message."
		delete shaderProgramInfoLog;
		return;
	}

	void PrintShaderCompilationErrorInfo(int32_t shaderID) {
		std::cout << "===============================\n";
		std::cout << "Shader compilation failed: " << std::endl;

		int maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		char* shaderInfoLog = new char[maxLength];
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, shaderInfoLog);

		std::cout << "\tError Info: " << shaderInfoLog << std::endl;

		std::cout << "===============================\n\n";
		delete shaderInfoLog;
	}

	std::string ReadFile(const char* file) {
		std::ifstream t(file);
		std::stringstream buffer;
		buffer << t.rdbuf();

		std::string fileContent = buffer.str();

		return fileContent;
	}

	GLuint shaderProgram;

	std::vector<int32_t> shaderIDs;
};

#endif