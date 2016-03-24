#include <iostream>
#include <string>

#include <SDL.h>

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <GL/GL.h>

// TODO-DG: Move these to a header?
SDL_Window* mainWindow = NULL;
SDL_GLContext mainContext;

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
void RunGame();
void Cleanup();

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

int main(int, char**) {
	if (!Init())
		return -1;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(mainWindow);

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
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					loop = false;
					break;
				case SDLK_r:
					glClearColor(1.0, 0.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(mainWindow);
					break;
				case SDLK_g:
					glClearColor(0.0, 1.0, 0.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(mainWindow);
					break;
				case SDLK_b:
					glClearColor(0.0, 0.0, 1.0, 1.0);
					glClear(GL_COLOR_BUFFER_BIT);
					SDL_GL_SwapWindow(mainWindow);
					break;
				default:
					break;
				}
			}
		}
	}
}

void Cleanup() {
	SDL_GL_DeleteContext(mainContext);

	SDL_DestroyWindow(mainWindow);

	SDL_Quit();
}

void CheckSDLError(int line = -1) {
	std::string error = SDL_GetError();

	if (error != "") {
		std::cout << "SDL Error: " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine: " << line << std::endl;

		SDL_ClearError();
	}
}

void PrintSDL_GL_Attributes() {
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION: " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}