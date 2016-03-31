#ifndef INCLUDE_ENTITY_HPP
#define INCLUDE_ENTITY_HPP

#pragma once

#include "Model.hpp"

class Entity {
public:
	Entity();

	void Init(glm::vec3 initialPosition = { 0,0,0 }, Model *initialModel = NULL);
	void Update(float deltaTime);
	void Render(glm::mat4 viewProjection);

	void AddVelocity(const glm::vec3 &_vel);
	glm::vec3 GetVelocity() { return mVelocity; }
	void SetModel(Model *model) { mModel = model; }
	glm::vec3 GetPosition() { return mPosition; }
	void SetPosition(const glm::vec3 &position) { mPosition = position; }
	void Translate(const glm::vec3 &movement) { 
		mPosition += movement; }

protected:
	glm::vec3 mPosition;
	glm::vec3 mVelocity;
	GLfloat maxVelocity;
private:
	Model *mModel;
};

#endif // !INCLUDE_ENTITY_HPP