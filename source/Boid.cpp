#include "Boid.hpp"

Boid::Boid() : windVector({1.0f, 0.0f, 0.0f}), goal(0.0f, 0.0f, 0.0f)
{
	Entity::maxVelocity = 50.0f;
}

// Calculate individual boid velocity
void Boid::Update(float deltaTime,const glm::vec3 &flockCenter, const glm::vec3 &localInfluence, const glm::vec3 &alignment) {
	/*** 
		MAIN RULES:
	***/
	// COHESION:
	glm::vec3 forceContribution;
	if (glm::length(flockCenter - GetPosition())) {
		forceContribution += glm::normalize(flockCenter - GetPosition()) * COHESION;	// NOTE: reverse drop-off function would probably be good for this to avoid too large results or constant contribution irregardless of distance
			// Note: Some implementations take the center excluding this boid's contribution, providing slightly different results.
			// Just something else to try :)
	}

	// SEPARATION:
	forceContribution += localInfluence * SEPARATION;

	// ALIGNMENT:
	forceContribution += alignment * ALIGNMENT;

	/***
		EXTRA RULES:
	***/
	// WIND:
	forceContribution += windVector * WIND;

	// GRAVITY:
	forceContribution += glm::vec3{ 0.0f, -1.0f, 0.0f } * GRAVITY;

	// GOAL SEEKING:
	if (glm::length(goal - GetPosition())) {
		forceContribution += glm::normalize(goal - GetPosition()) * GOAL;
	}
	

	// TODO-Opt: Extra rules to try:
	// Perching, resting on ground for short periods

	
	SetForce(forceContribution);
	Entity::Update(deltaTime);
}
