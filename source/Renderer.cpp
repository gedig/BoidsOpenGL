#include "Renderer.hpp"

Renderer::Renderer()
{
}

bool Renderer::Init() {
	// Initialize SDL's Video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to init SDL\n";
		return false;
	}

	// Create our window centered at 512x512 resolution
	mainWindow = SDL_CreateWindow("BoidsSDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	// Check that everything worked out okay
	if (!mainWindow) {
		std::cout << "Unable to create window\n" << std::endl;;
		CheckSDLError(__LINE__);
		return false;
	}

	SetSDL_GL_Attributes();

	// Create our opengl context and attach it to our window
	mainContext = SDL_GL_CreateContext(mainWindow);

	SDL_GL_SetSwapInterval(1);	// Vsync enabled

	// Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	SetOpenGLOptions();

	return true;
}

// Method that starts rendering on each step.
void Renderer::RenderStart() {
	glClearColor(0.5, 0.5, 0.5, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Called at the end for cleanup and to swap the buffers
void Renderer::RenderEnd() {
	SDL_GL_SwapWindow(mainWindow);
}

void Renderer::Cleanup() {
	SDL_GL_DeleteContext(mainContext);

	SDL_DestroyWindow(mainWindow);

	SDL_Quit();
}

void Renderer::CheckSDLError(int line) {
	std::string error = SDL_GetError();

	if (error != "") {
		std::cout << "SDL Error: " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine: " << line << std::endl;

		SDL_ClearError();
	}
}

// This set our extra OpenGL options we'll need
void Renderer::SetOpenGLOptions()
{
	// Enable blending for transparent objects
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth testing so that closer triangles will hide the triangles farther away
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

bool Renderer::SetSDL_GL_Attributes()
{
	// Set our OpenGL version.
	// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}