#pragma once
#include "Material.h"
class Dielectric :
	public Material
{
public:
	float refractive_ind;
	Dielectric(float refractive_ind) { this->refractive_ind = refractive_ind; }
	virtual bool scatter(Ray& r, hit_record& rec, glm::vec3&attenuation, Ray& scattered);
};

