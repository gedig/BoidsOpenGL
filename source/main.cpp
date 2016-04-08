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
	cameraFlockDistance = INITIAL_CAMERA_DISTANCE;
	camera.Init();
	cameraVerticalLockTime = -1.0f;
	floorGrid.Init();
	glm::vec3 bottomLeftBound = { -floorGrid.GetFieldSize(), 0.0f, -floorGrid.GetFieldSize() };
	glm::vec3 topRightBound = { floorGrid.GetFieldSize(), floorGrid.GetFieldSize() / 2.0f, floorGrid.GetFieldSize() };
	boidModel.Init("boid");
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].Init(glm::vec3(), &boidModel);
		boids[i].SetBounds(bottomLeftBound, topRightBound, BOUNDS_BOUNCE);
		boids[i].SetGoal({ 0.0f, INITIAL_HEIGHT, 0.0f });
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
		else if (eventHandler.Reset()) {
			Reset();
		}
		else {
			Update();
		}
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
	glm::vec3 initialCameraPosition = glm::vec3(0, INITIAL_DISTANCE * 1.5f, -INITIAL_CAMERA_DISTANCE);
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
	for (int i = 0; i < NUM_BOIDS; i++) {
		center += boids[i].GetPosition();
		if (glm::length(boids[i].GetVelocity())) {
			alignment += glm::normalize(boids[i].GetVelocity());
		}
		/* // NOTE: Experimented with using this as well with some very interesting results, more fluid appearing and more likely to reach equilibrium
		if (glm::length(boids[i].GetForce())) {
			alignment += glm::normalize(boids[i].GetForce());
		}*/
		for (int j = i+1; j < NUM_BOIDS; j++) {
			glm::vec3 distanceVec = boids[i].GetPosition() - boids[j].GetPosition();
			GLfloat distance = glm::length(distanceVec);
			
			if (distance < SEPARATION_DISTANCE && distance > 0.0f) {
				GLfloat contribution = 0.0f;
				// Smooth exponential dropoff from http://webhome.cs.uvic.ca/~blob/publications/datastructures.pdf
				contribution = (-0.444444f * pow(distance, 6) / pow(SEPARATION_DISTANCE, 6)) + (1.888889f * pow(distance, 4) / pow(SEPARATION_DISTANCE, 4)) + (-2.444444f * pow(distance, 2) / pow(SEPARATION_DISTANCE, 2)) + 1.0f;
				
				// Linear:
				//contribution = SEPARATION_DISTANCE - distance;

				localInfluence[i] += glm::normalize(distanceVec) * contribution;
				localInfluence[j] -= glm::normalize(distanceVec) * contribution;
				// Updating both of these is a bit better than O(n^2) :)
			}
		}
	}

	center *= (1.0f/NUM_BOIDS);
	alignment *= (1.0f / NUM_BOIDS);

	// Update Each Boid.
	for (int i = 0; i < NUM_BOIDS; i++) {
		boids[i].Update(deltaTime * TIME_MOD, center, localInfluence[i], alignment);
	}
	// End Boids

	// Update the camera

	// Handle Movement
	std::vector<Event> events = eventHandler.GetEvents();
	for (int i = 0; i < events.size(); i++) {
		switch (events[i].type) {
		case EventType::CameraRotation:
				switch (events[i].action) {
				case EventAction::Left:
					camera.RotateLeft(center, CAMERA_ROTATE_SPEED * deltaTime);
						break;
				case EventAction::Right:
					camera.RotateRight(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				case EventAction::Up:
					cameraVerticalLockTime = CAMERA_LOCK_TIME;
					camera.RotateUp(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				case EventAction::Down:
					camera.RotateDown(center, CAMERA_ROTATE_SPEED * deltaTime);
					break;
				default:
					break;
				}
			break;
		case EventType::CameraDolly:
			if (events[i].action == EventAction::Up) {
				cameraFlockDistance -= CAMERA_DOLLY_SPEED * deltaTime;
			}
			else {
				cameraFlockDistance += CAMERA_DOLLY_SPEED * deltaTime;
			}
			break;
		default:
			break;
		}
	}

	// Move Camera near cameraFlockdistance
	if (glm::length(camera.GetPosition() - center) > 0.0f) {
		glm::vec3 targetPoint = (glm::normalize(camera.GetPosition() - center) * cameraFlockDistance) + center;
		if (cameraVerticalLockTime > 0.0f) {
			targetPoint.y = camera.GetPosition().y;
			cameraVerticalLockTime -= deltaTime;
		}
		if (glm::distance(targetPoint, camera.GetPosition()) > CAMERA_MOVE_THRESHOLD) {
			camera.Translate((targetPoint - camera.GetPosition()) * CAMERA_SPEED_MOD * deltaTime);
		}
		camera.SetLookTarget(center);
	}
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