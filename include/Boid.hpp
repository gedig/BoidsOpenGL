#ifndef INCLUDE_BOID_HPP
#define INCLUDE_BOID_HPP

#pragma once

#include "Entity.hpp"

#define COHESION 1.7f
#define SEPARATION 12.0f

class Boid : public Entity {
public:
	Boid();

	void Update(float deltaTime,const glm::vec3 &flockCenter, const glm::vec3 &localInfluence, const glm::vec3 alignment);
};

#endif // !INCLUDE_BOID_HPP