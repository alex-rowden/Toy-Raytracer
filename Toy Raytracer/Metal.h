#pragma once
#include "Material.h"
#define MIN(a,b) a < b ? a : b 

class Metal :
	public Material
{
public:
	glm::vec3 albedo;
	float fuzziness;
	Metal() {}
	Metal(glm::vec3 albedo_) :albedo(albedo_) { fuzziness = 0; }
	Metal(glm::vec3 albedo_, float fuzziness) :albedo(albedo_) { this->fuzziness = MIN(fuzziness, 1); }
	virtual bool scatter(Ray& r_in, hit_record& rec, glm::vec3& attenuation, Ray& scattered);
};

