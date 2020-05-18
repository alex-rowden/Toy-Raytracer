#pragma once
#include "Material.h"
#include "MyRandom.h"
#include <random>
#include <chrono>



class Lambertian :
	public Material
{
public:
	glm::vec3 albedo;

	Lambertian(glm::vec3 albedo_){ albedo = albedo_; }
	virtual bool scatter(Ray& r, hit_record&rec, glm::vec3&attenuation, Ray&scatter) ;

};

