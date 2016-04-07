#include "Entity.hpp"

Entity::Entity() : maxVelocity(-1.0f), mMass(1.0f)
{
}

void Entity::Init(glm::vec3 initialPosition, Model *initialModel){
	prevPosition = mPosition = initialPosition;
	mModel = initialModel;
}

void Entity::Update(float deltaTime) {
	// Apply velocity to position
	// Euler Int:
	//mPosition += mVelocity * deltaTime;

	// Verlet Int:
	SetVelocity((GetPosition() - prevPosition) * 0.99f);
	SetPosition(GetPosition() + mVelocity + (mForce / mMass) * deltaTime *deltaTime);
}

void Entity::Render(glm::mat4 viewProjection){
	glm::mat4 modelMatrix = glm::translate(glm::mat4(), mPosition);
	mModel->SetMatrix(viewProjection * modelMatrix);
	mModel->Render();
}

void Entity::SetVelocity(const glm::vec3 & _vel)
{
	mVelocity = _vel;
	if (maxVelocity > -2.0f) {
		if (glm::length(mVelocity) > maxVelocity) {
			mVelocity = glm::normalize(mVelocity) * maxVelocity;
		}
	}
}

void Entity::SetPosition(const glm::vec3 & position, bool reset)
{
	if (reset) {
		prevPosition = position;
	} else {
		prevPosition = mPosition;
	}
	
	mPosition = position;
	// Bounds only for boids, currently, change if this is used elsewhere
	if (mPosition.y < 0) {
		mPosition.y = 0;
	}
}
