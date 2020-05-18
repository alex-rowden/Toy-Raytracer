#include "Material.h"
#define M_PI 3.1415926535897932384626433

float Material::schlick(float cosine, float refractive_ind) {
	float r0 = (1 - refractive_ind) / (1 + refractive_ind);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}

bool Material::refract(const glm::vec3& v, const glm::vec3& n, float refractive_ind, glm::vec3& refracted) {
	glm::vec3 uv = glm::normalize(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - refractive_ind * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = refractive_ind * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

glm::vec3 Material::reflect(const glm::vec3& v, const glm::vec3& n) {
	return v - 2 * glm::dot(v, n) * n;
}

float Material::uniform01() {
	return rand() / (float)RAND_MAX;
}
glm::vec3 Material::random_in_unit_sphere() {
	float theta = 2 * M_PI * uniform01();
	float phi = acos(1 - 2 * uniform01());
	return glm::vec3(sin(phi) * cos(theta), sin(phi) * sin(theta), cos(phi));
}