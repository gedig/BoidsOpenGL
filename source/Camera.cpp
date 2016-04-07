#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
}

void Camera::Init(glm::vec3 initPos) {
	mPosition = initPos;	// TODO-DG: Read this in from file here instead of being passed in?
	// Currently, lookTarget defaults to origin.
	projection = glm::perspective(
		45.0f,	// Field of View
		1.0f,	// Aspect Ratio
		1.0f,	// Near Plane
		1000.0f);// Far Plane
}

glm::mat4 Camera::GetViewProjection()
{
	glm::mat4 view = glm::lookAt(
		mPosition,
		lookTarget,
		glm::vec3(0, 1, 0));
	return projection * view;;
}