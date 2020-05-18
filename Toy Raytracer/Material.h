#pragma once
#include <glm.hpp>
#include "Ray.h"
#include "Object.h"
class Material
{
public:
	virtual bool scatter(Ray&r, hit_record&rec, glm::vec3&attenuation, Ray&scattered)  = 0;
	glm::vec3 random_in_unit_sphere();
	glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n);
	bool refract(const glm::vec3&v, const glm::vec3&n, float refractive_ind, glm::vec3&refracted);
	float schlick(float cosine, float refractive_ind);
	float uniform01();
};

