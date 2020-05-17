#pragma once
#include <glm.hpp>
class Ray {
private:
	glm::vec3 origin, direction;
public:
	/*
	origin		~	The starting location of the ray in global coordinates.
	direction	~	The normalized direction the ray is pointing.
	*/
	Ray() {};
	Ray(glm::vec3 origin, glm::vec3 direction) { this->origin = origin; this->direction = glm::normalize(direction); };
	glm::vec3 getDirection() { return this->direction; }
	glm::vec3 getOrigin() { return this->origin; }
	glm::vec3 getPositionAlongRay(float t) { return this->direction* t + this->origin; }

};