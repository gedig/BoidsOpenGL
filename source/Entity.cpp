#include "Entity.hpp"

Entity::Entity() : maxVelocity(-1.0f)
{
}

void Entity::Init(glm::vec3 initialPosition, Model *initialModel){
	mPosition = initialPosition;
	mModel = initialModel;
}

void Entity::Update(float deltaTime) {
	// Apply velocity to position
	mPosition += mVelocity * deltaTime;
}

void Entity::Render(glm::mat4 viewProjection){
	glm::mat4 modelMatrix = glm::translate(glm::mat4(), mPosition);
	mModel->SetMatrix(viewProjection * modelMatrix);
	mModel->Render();
}

void Entity::AddVelocity(const glm::vec3 & _vel)
{
	mVelocity += _vel;
	if (maxVelocity > -2.0f) {
		if (mVelocity.length() > maxVelocity) {
			mVelocity = glm::normalize(mVelocity) * maxVelocity;
		}
	}
}
