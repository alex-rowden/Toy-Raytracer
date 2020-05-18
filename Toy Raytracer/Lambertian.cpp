#include "Lambertian.h"

bool Lambertian::scatter(Ray& r, hit_record&rec, glm::vec3&attenuation, Ray&scattered) 
{
	glm::vec3 target(rec.position + rec.normal + random_in_unit_sphere());
	scattered = Ray(rec.position, glm::normalize(target - rec.position));
	attenuation = albedo;
	return true;
}
