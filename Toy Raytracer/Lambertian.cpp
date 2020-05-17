#include "Lambertian.h"

float uniform01() {
	return rand() / (float)RAND_MAX;
}

glm::vec3 random_in_unit_sphere() {
	float theta = 2 * M_PI * uniform01();
	float phi = acos(1 - 2 * uniform01());
	return glm::vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}

bool Lambertian::scatter(Ray& r, hit_record rec, glm::vec3&attenuation, Ray&scattered) 
{
	glm::vec3 target(rec.position + rec.normal);
	scattered = Ray(rec.position, target - rec.position);
	attenuation = albedo;
	return true;
}
