#include "Entity.hpp"

Entity::Entity() : bounds(false), maxVelocity(-1.0f), mMass(1.0f), mVelocity(0.0f)
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
	SetVelocity((GetPosition() - prevPosition) * 0.999f);
	Translate( mVelocity + (mForce / mMass) * deltaTime *deltaTime);
}

void Entity::Render(glm::mat4 viewProjection){
	glm::mat4 modelMatrix = glm::translate(glm::mat4(), mPosition);
	mModel->SetMatrix(viewProjection * modelMatrix);
	mModel->Render();
}

void Entity::SetBounds(const glm::vec3 & bl, const glm::vec3 & tr, GLfloat bounceAmount)
{
	bounds = true; 
	bottomLeftBound = bl; 
	topRightBound = tr; 
	boundsBounce = bounceAmount;
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
}

void Entity::Translate(const glm::vec3 & movement)
{
	prevPosition = mPosition;
	mPosition += movement;

	if (bounds) {
		if (mPosition.x < bottomLeftBound.x) {
			mPosition.x = bottomLeftBound.x;
			prevPosition.x = bottomLeftBound.x - boundsBounce;
		}
		else if (mPosition.x > topRightBound.x) {
			mPosition.x = topRightBound.x;
			prevPosition.x = topRightBound.x + boundsBounce;
		}
		if (mPosition.y < bottomLeftBound.y) {
			mPosition.y = bottomLeftBound.y;
			prevPosition.y = bottomLeftBound.y - boundsBounce;
		}
		else if (mPosition.y > topRightBound.y) {
			mPosition.y = topRightBound.y;
			prevPosition.y = topRightBound.y + boundsBounce;
		}
		if (mPosition.z < bottomLeftBound.z) {
			mPosition.z = bottomLeftBound.z;
			prevPosition.z = bottomLeftBound.z - boundsBounce;
		}
		else if (mPosition.z > topRightBound.z) {
			mPosition.z = topRightBound.z;
			prevPosition.z = topRightBound.z + boundsBounce;
		}
	}
}
