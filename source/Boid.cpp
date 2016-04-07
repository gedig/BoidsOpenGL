#include "Boid.hpp"

Boid::Boid()
{
	Entity::maxVelocity = 1.0f;
}

void Boid::Update(float deltaTime,const glm::vec3 &flockCenter, const glm::vec3 &localInfluence, const glm::vec3 alignment) {
	// Calculate individual boid velocity
	// COHESION:
	glm::vec3 forceContribution = flockCenter - GetPosition() * COHESION;
	// Note: Some implementations take the center excluding this boid's contribution, providing slightly different results.
	// Just something else to try :)

	// SEPARATION:
	forceContribution += localInfluence * SEPARATION;

	// TODO-DG: lerp from our current normalized velocity to that of the flock.



	// TODO-Opt: Extra rules to try:
	//	Wind
	//	Goal-Setting (paths)
	// Perching, resting on ground for short periods

	
	SetForce(forceContribution);
	Entity::Update(deltaTime);
}
