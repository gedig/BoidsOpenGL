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
		glm::vec3(0, 1, 0));	// TODO-Opt: We could update the third glm::lookAt vector if we want the camera to "bank" while turning!
	return projection * view;;
}

void Camera::RotateLeft(const glm::vec3 &_point, float angle) {
	RotateAround(_point, { 0.0f, 1.0f, 0.0f }, -angle);
}

void Camera::RotateRight(const glm::vec3 &_point, float angle) {
	RotateAround(_point, { 0.0f, 1.0f, 0.0f }, angle);
}

void Camera::RotateUp(const glm::vec3 &_point, float angle) {
	glm::vec3 cross = glm::cross(GetPosition() - _point, { 0.0f, 1.0f, 0.0f });
	RotateAround(_point, cross, angle);
}

void Camera::RotateDown(const glm::vec3 &_point, float angle) {
	RotateUp(_point, -angle);
}

void Camera::RotateAround(const glm::vec3 &_point, const glm::vec3 &_axis, float angle)
{
	glm::vec3 pos = GetPosition();
	glm::vec3 axis = glm::normalize(_axis);
	// Build rotation quat from angle axis
	glm::quat rot;
	float s = sin(angle / 2.0f);
	rot.x = axis.x * s;
	rot.y = axis.y * s;
	rot.z = axis.z * s;
	rot.w = cos(angle / 2.0f);

	glm::vec3 dir = pos - _point;
	dir = rot * dir;
	pos = _point + dir;
	SetPosition(pos);
}
