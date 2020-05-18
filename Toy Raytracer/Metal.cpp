#include "Metal.h"



bool Metal::scatter(Ray& r_in, hit_record& rec, glm::vec3& attenuation, Ray& scattered) {
	glm::vec3 reflected = reflect(glm::normalize(r_in.getDirection()), rec.normal);
	scattered = Ray(rec.position, reflected + fuzziness * random_in_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.getDirection(), rec.normal) > 0);
}

