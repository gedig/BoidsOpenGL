#ifndef INCLUDE_RENDERER_HPP
#define INCLUDE_RENDERER_HPP

#pragma once

#include "Model.hpp"
#include "ShaderProgram.hpp"

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL.h>

class Renderer {
public:
	Renderer();

	bool Init();

	void RenderStart();
	void RenderEnd();
	void Cleanup();
	void CheckSDLError(int line = -1);

private:
	void SetOpenGLOptions();
	bool SetSDL_GL_Attributes();

	SDL_Window* mainWindow;
	SDL_GLContext mainContext;
};

#endif