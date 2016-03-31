#include "main.hpp"

/**************************************************/
/**	Main/Update/Render	**/
/**************************************************/
int main(int, char**) {
	if (!renderer.Init()) {
		return -1;
	}
	camera.Init();
	boidModel.Init("boid");
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].Init(glm::vec3(), &boidModel);
	}
	Reset();	// Sets the scene.

	// Main Game Loop
	bool running = true;
	while (running) {
		eventHandler.Update();

		if (eventHandler.Quit()) {
			running = false;
			break;
		}
		Update();
		Render();
	}

	renderer.Cleanup();

	return 0;
}

void Reset() {
	glm::vec3 initialCameraPosition = glm::vec3(0, NUM_ROWS*INITIAL_DISTANCE / 2.0f, -50);
	camera.SetPosition(initialCameraPosition);

	// TODO-DG: Might be a good idea to randomize the starting positions
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].SetPosition({ ((i % NUM_COLS) - NUM_COLS / 2.0f)*INITIAL_DISTANCE, (i / 10)*(INITIAL_DISTANCE), 0.0f });
	}
}

void Update() {
	GLint64 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - prevTime) / 1000.0f;
	prevTime = currentTime;

	// BOIDS:
	// Calculate the center of mass.
	//	& calculate the optimal direction to steer to avoid nearby boids
	glm::vec3 center;
	glm::vec3 alignment;
	glm::vec3 localInfluence[NUM_BOIDS];
	for (int i = 0; i < NUM_BOIDS; i++) {
		center += boids[i].GetPosition();
		alignment += glm::normalize(boids[i].GetVelocity());
		for (int j = i+1; j < NUM_BOIDS; j++) {
			glm::vec3 distanceVec = boids[i].GetPosition() - boids[j].GetPosition();
			if (distanceVec.length() > SEPARATION_DISTANCE) {
				// Can calculate different styles of dropoff here, using linear for now.
				GLfloat contribution = SEPARATION_DISTANCE - distanceVec.length();
				localInfluence[i] += glm::normalize(distanceVec) * contribution;
				localInfluence[j] += glm::normalize(distanceVec) * contribution;
				// Updating both of these is better than O(n^2) :)
			}
		}
	}

	center *= (1.0f/NUM_BOIDS);

	// Update Each Boid.
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].Update(deltaTime, center, localInfluence[i], alignment);
	}
	// End Boids

	// Update the camera
	// TODO-DG: Better camera movement!
	if (glm::distance(camera.GetPosition(), center) > MIN_CAMERA_DISTANCE) {
		camera.Translate(glm::normalize(center - camera.GetPosition()) * MAX_CAMERA_SPEED * deltaTime);
	}	// TODO-DG: Else what? Back up? Start strafing out of the way? The boids are coming!
	camera.SetLookTarget(center);
	// TODO-Opt: We could update the third glm::lookAt vector if we want the camera to "bank" while turning!
}

void Render() {
	renderer.RenderStart();
	for (int i = 0; i < NUM_BOIDS; i++) {
		glm::mat4 viewProj = camera.GetViewProjection();
		boids[i].Render(camera.GetViewProjection());
	}
	renderer.RenderEnd();
}