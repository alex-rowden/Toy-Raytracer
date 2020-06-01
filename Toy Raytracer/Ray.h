#pragma once
#include <glm.hpp>
class Ray {
private:
	glm::vec3 origin, direction;
	float time;
public:
	/*
	origin		~	The starting location of the ray in global coordinates.
	direction	~	The normalized direction the ray is pointing.
	*/
	Ray() {};
	Ray(glm::vec3 origin, glm::vec3 direction) { this->origin = origin; this->direction = glm::normalize(direction); this->time = 0; };
	Ray(glm::vec3 origin, glm::vec3 direction, float t) { this->origin = origin; this->direction = glm::normalize(direction); this->time = t; };
	glm::vec3 getDirection() const { return glm::normalize(this->direction); }
	glm::vec3 getOrigin() const { return this->origin; }
	glm::vec3 getPositionAlongRay(float t) { return this->direction* t + this->origin; }
	float getTime() { return this->time; }
};