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
	MyRandom random;
	
	Lambertian(glm::vec3 albedo_, MyRandom random_) :random(random_){ albedo = albedo_; }

	virtual bool scatter(Ray& r, hit_record, glm::vec3&attenuation, Ray&scatter) ;

};

