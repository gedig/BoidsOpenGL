#include "main.hpp"
#include <time.h>

/**************************************************/
/**	Main/Update/Render	**/
/**************************************************/
int main(int, char**) {
	srand(time(NULL));
	if (!renderer.Init()) {
		return -1;
	}
	camera.Init();
	floorGrid.Init();
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
		eventHandler.ClearEvents();
	}

	renderer.Cleanup();

	return 0;
}

float RandomMod(float offset = 0.0f) {
	float smallRand = (float)rand() / RAND_MAX;
	return (smallRand - offset) * INITIAL_DISTANCE * (1.0f + offset);
}

void Reset() {
	glm::vec3 initialCameraPosition = glm::vec3(0, INITIAL_DISTANCE * 2, -50);
	camera.SetPosition(initialCameraPosition);

	for (int i = 0; i < NUM_BOIDS; i++) {
		glm::vec3 pos = { RandomMod(1.0f), RandomMod() + INITIAL_HEIGHT, RandomMod(1.0f) };
		boids[i].SetPosition(pos, true);
	}
}

void Update() {
	GLint64 currentTime = SDL_GetTicks();
	float deltaTime = (currentTime - prevTime) / 1000.0f;
	prevTime = currentTime;

	// BOIDS:
	// Calculate the center of mass.
	//	& calculate the optimal direction to steer to avoid nearby boids
	glm::vec3 center(0.0f);
	glm::vec3 alignment(0.0f);
	glm::vec3 localInfluence[NUM_BOIDS];
	int numInfluencers[NUM_BOIDS] = { 0 };
	for (int i = 0; i < NUM_BOIDS; i++) {
		center += boids[i].GetPosition();
		alignment += glm::normalize(boids[i].GetVelocity());
		for (int j = i+1; j < NUM_BOIDS; j++) {
			glm::vec3 distanceVec = boids[i].GetPosition() - boids[j].GetPosition();
			if (glm::length(distanceVec) < SEPARATION_DISTANCE) {
				// Can calculate different styles of dropoff here, using linear for now.
				GLfloat contribution = SEPARATION_DISTANCE - glm::length(distanceVec);
				localInfluence[i] += glm::normalize(distanceVec) * contribution;
				localInfluence[j] += glm::normalize(distanceVec) * contribution;
				numInfluencers[i]++;
				numInfluencers[j]++;
				// Updating both of these is better than O(n^2) :)
			}
		}
	}

	center *= (1.0f/NUM_BOIDS);
	alignment *= (1.0f / NUM_BOIDS);

	// Update Each Boid.
	for (int i = 0; i < NUM_BOIDS; i++) {
		if (numInfluencers[i] > 0) {
			localInfluence[i] *= (0.5f / numInfluencers[i]);
		}
		boids[i].Update(deltaTime, center, localInfluence[i], alignment);
	}
	// End Boids

	// Update the camera

	// Handle Movement
	bool autoMove = true;
	bool autoRotate = true;
	std::vector<Event> events = eventHandler.GetEvents();
	for (int i = 0; i < events.size(); i++) {
		switch (events[i].type) {
		case EventType::CameraRotation:
			autoMove = false;
				switch (events[i].action) {
				case EventAction::Left:
					camera.RotateLeft(center, CAMERA_ROTATE_SPEED * deltaTime);
						break;
				case EventAction::Right:
					camera.RotateRight(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				case EventAction::Up:
					camera.RotateUp(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				case EventAction::Down:
					camera.RotateDown(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				default:
					break;
				}
			break;
		}
	}
	if (autoMove) {
		if (glm::distance(camera.GetPosition(), center) > MIN_CAMERA_DISTANCE) {
			camera.Translate(glm::normalize(center - camera.GetPosition()) * MAX_CAMERA_SPEED * deltaTime);
		}	// TODO-DG: Else what? Back up? Start strafing out of the way? The boids are coming!
	}
	if (autoRotate) {
		camera.SetLookTarget(center);
	}
	// TODO-Opt: We could update the third glm::lookAt vector if we want the camera to "bank" while turning!
}

void Render() {
	renderer.RenderStart();
	glm::mat4 viewProj = camera.GetViewProjection();
	floorGrid.Render(viewProj);
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].Render(viewProj);
	}
	renderer.RenderEnd();
}