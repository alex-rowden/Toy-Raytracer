#include "Dielectric.h"

bool Dielectric::scatter(Ray& r, hit_record& rec, glm::vec3& attenuation, Ray& scattered)
{
	glm::vec3 outward_normal;
	glm::vec3 reflected = reflect(r.getDirection(), rec.normal);
	float refractive_ind;
	attenuation = glm::vec3(1, 1, 1);
	glm::vec3 refracted;
	float reflect_prob;
	float cosine;
	if (dot(r.getDirection(), rec.normal) > 0) {
		outward_normal = -rec.normal;
		refractive_ind = this->refractive_ind;
		cosine = refractive_ind * dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}
	else {
		outward_normal = rec.normal;
		refractive_ind = 1 / this->refractive_ind;
		cosine = -dot(r.getDirection(), rec.normal) / r.getDirection().length();
	}if (refract(r.getDirection(), outward_normal, refractive_ind, refracted)) {
		reflect_prob = schlick(cosine, refractive_ind);
	}
	else {
		reflect_prob = 1.0;
	}if(uniform01() < reflect_prob){
		scattered = Ray(rec.position, reflected, r.getTime());
	}else {
		scattered = Ray(rec.position, refracted, r.getTime());
		//return false;
	}
	return true;
}
