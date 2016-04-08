#ifndef INCLUDE_BOID_HPP
#define INCLUDE_BOID_HPP

#pragma once

#include "Entity.hpp"
//		Field Modifier:		Recommended Value:		// Notes:
#define COHESION 4.0f
#define SEPARATION 5.0f		//						// Depends greatly on linear or dropoff, main.hpp also has a SEPARATION_DISTANCE constant directly tied to this
#define ALIGNMENT 8.0f		
#define WIND 0.5f
#define GRAVITY 0.1f 
#define GOAL 6.5f

class Boid : public Entity {
public:
	Boid();

	void Update(float deltaTime,const glm::vec3 &flockCenter, const glm::vec3 &localInfluence, const glm::vec3 &alignment);

	void SetWind(const glm::vec3 &_wind) { windVector = _wind; }
	void SetGoal(const glm::vec3 &_goal) { goal = _goal; }

private:
	glm::vec3 windVector;
	glm::vec3 goal;
};

#endif // !INCLUDE_BOID_HPP