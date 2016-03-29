#ifndef INCLUDE_CAMERA_HPP
#define INCLUDE_CAMERA_HPP

#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	Camera();

	void Init();

	glm::mat4 GetViewProjection() { return projection * view; }
private:
	glm::mat4 projection;
	glm::mat4 view;
};

#endif // !INCLUDE_CAMERA_HPP