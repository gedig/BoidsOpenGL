#ifndef INCLUDE_MAIN_HPP
#define INCLUDE_MAIN_HPP

#pragma once

#include <SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/GL.h>

#include "ShaderHelper.hpp"

SDL_Window* mainWindow = NULL;
SDL_GLContext mainContext;

// Object Info:
const uint32_t points = 12;
const uint32_t floatsPerPoint = 3;
const uint32_t floatsPerColour = 4;

// Temp Object to draw
const GLfloat diamond[points][floatsPerPoint] = {
	{ 0.2,  0.2,  0.5 }, // Top right
	{ -0.2,  0.2,  0.5 }, // Top left
	{ 0.0,  0.0,  0.5 }, // Center

	{ 0.2,  0.2,  0.5 }, // Top right
	{ 0.2, -0.2,  0.5 }, // Bottom right 
	{ 0.0,  0.0,  0.5 }, // Center

	{ -0.2, -0.2,  0.5 }, // Bottom left
	{ 0.2, -0.2,  0.5 }, // Bottom right 
	{ 0.0,  0.0,  0.5 }, // Center

	{ -0.2, -0.2,  0.5 }, // Bottom left
	{ -0.2,  0.2,  0.5 }, // Top left
	{ 0.0,  0.0,  0.5 }, // Center
};
const GLfloat colours[points][floatsPerColour] = {
	{ 0.5, 0.5, 0.5, 1.0f }, // Top right
	{ 0.5, 0.5, 0.5, 1.0f }, // Bottom right 
	{ 0.0, 0.0, 0.0, 1.0f }, // Center

	{ 0.5, 0.5, 0.5, 1.0f }, // Top left
	{ 0.5, 0.5, 0.5, 1.0f }, // Top right
	{ 0.0, 0.0, 0.0, 1.0f }, // Center

	{ 0.5, 0.5, 0.5, 1.0f }, // Bottom left
	{ 0.5, 0.5, 0.5, 1.0f }, // Bottom right 
	{ 0.0, 0.0, 0.0, 1.0f }, // Center

	{ 0.5, 0.5, 0.5, 1.0f }, // Bottom left
	{ 0.5, 0.5, 0.5, 1.0f }, // Top left
	{ 0.0, 0.0, 0.0, 1.0f }, // Center
};

// Vars for VAO&VBO ids
GLuint vbo[2], vao[1];

const uint32_t positionAttributeIndex = 0, colourAttributeIndex = 1;

ShaderHelper shaderHelper;

bool error = false;

void CheckSDLError(int line);
bool Init();
bool SetOpenGLAttributes();
bool SetupBufferObjects();
void Render();
void RunGame();
void Cleanup();

#endif