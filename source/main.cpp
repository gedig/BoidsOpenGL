#include "main.hpp"
#include <iostream>
#include <string>

// **********************************
// Main Methods, update&render, etc.
int main(int, char**) {
	if (!Init())
		return -1;

	// Apply a gray background
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);

	if (!SetupBufferObjects())
		error = true;

	RunGame();

	Cleanup();

	return 0;
}

void RunGame() {
	bool loop = true;

	while (loop) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				loop = false;
			if (!error)
				Render();
		}
	}
}

void Render() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnableVertexAttribArray(colourAttributeIndex);
	glDrawArrays(GL_TRIANGLES, 0, points);

	SDL_GL_SwapWindow(mainWindow);
}

// **********************************
// Helper functions (alphabetical)

void CheckSDLError(int line = -1) {
	std::string error = SDL_GetError();

	if (error != "") {
		std::cout << "SDL Error: " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine: " << line << std::endl;

		SDL_ClearError();
	}
}

void Cleanup() {
	shaderHelper.CleanUp();

	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);

	SDL_GL_DeleteContext(mainContext);

	SDL_DestroyWindow(mainWindow);

	SDL_Quit();
}

bool Init() {
	if (SDL_Init(SDL_INIT_VIDEO < 0)) {
		std::cout << "Failed to initialize SDL." << std::endl;
		return 1;
	}
	mainWindow = SDL_CreateWindow("SDLBoids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);

	if (!mainWindow) {
		std::cout << "Window Creation Failure\n";
		CheckSDLError(__LINE__);
		return false;
	}

	SetOpenGLAttributes();

	// Create our OpenGL Context and attach it to the window.
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetSwapInterval(1);

	// Might be useful:
	glewExperimental = GL_TRUE;
	glewInit();
	return true;
}

bool SetOpenGLAttributes() {
	// Prevents us from using deprecated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

bool SetupBufferObjects() {
	// Generates 2 vertex buffers to our handle
	glGenBuffers(2, vbo);
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	// First VBO is active buffer with positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (points * floatsPerPoint) * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

	// Coordinate data goes into attribute index 0 and contains 3 floats per vertex
	glVertexAttribPointer(positionAttributeIndex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(positionAttributeIndex);

	// Next VBO is colour data.
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, (points*floatsPerColour) * sizeof(GL_FLOAT), colours, GL_STATIC_DRAW);

	glVertexAttribPointer(colourAttributeIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(colourAttributeIndex);

	if (!shaderHelper.Init("boid"))
		return false;

	shaderHelper.UseProgram();

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}