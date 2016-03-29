#include "main.hpp"

/**************************************************/
/**	Main/Update/Render	**/
/**************************************************/
int main(int, char**) {
	if (!renderer.Init()) {
		return -1;
	}
	camera.Init();

	Model tempModel;
	tempModel.Init("boid");	// TODO-DG: Error check this.
	
	modelList.push_back(tempModel);

	// Main Game Loop
	bool running = true;
	while (running) {
		eventHandler.Update();

		if (eventHandler.Quit()) {
			running = false;
			break;
		}
		if (eventHandler.IsKeyDown(SDLK_r)) {
			Reset();
		} else {
			Update();
		}
		Render();
	}

	renderer.Cleanup();

	return 0;
}

void Reset() {
	for (int i = 0; i < modelList.size(); i++) {
		modelList[i].ResetMatrix();
	}
}

void Update() {
	for (int i = 0; i < modelList.size(); i++) {
		modelList[i].Update();
	}
}

void Render() {
	renderer.RenderStart();
	for (int i = 0; i < modelList.size(); i++) {
		glm::mat4 mvp = camera.GetViewProjection() * modelList[i].getModel();
		modelList[i].SetMatrix(mvp);
		modelList[i].Render();
	}
	renderer.RenderEnd();
}