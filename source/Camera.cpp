#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

void Camera::Init() {
	// Set up initial camera matrices.
	projection = glm::perspective(
		45.0f,	// Field of View
		1.0f,	// Aspect Ratio
		0.1f,	// Near Plane
		100.0f);// Far Plane

	view = glm::lookAt(
		glm::vec3(-2, 0, -4),	// Camera start point
		glm::vec3(0, 0, 0),		// Begins looking at the origin
		glm::vec3(0, 1, 0));	// Head begins looking up
}
