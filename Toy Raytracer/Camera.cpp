#include "Camera.h"

float Camera::uniform01() {
	return rand() / (float)RAND_MAX;
}
glm::vec3 Camera::random_in_unit_disk() {
	float theta = 2 * M_PI * uniform01();
	float r = uniform01();
	return glm::vec3(r * sin(theta), r * cos(theta), 0);
}

Camera::Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect, float aperature, float focus_dist) {
	this->lens_radius = aperature / 2.f;
	
	float theta = fov * M_PI / 180.0f;
	float half_height = tan(theta / 2.0f);
	float half_width = aspect * half_height;
	this->origin = position;
	this->w = glm::normalize(position - lookat);
	this->u = glm::normalize(glm::cross(up, w));
	this->v = glm::normalize(glm::cross(w, u));
	//lower_left_corner = glm::vec3(-half_width, -half_height, -1.0);
	
	this->horizontal = 2 * half_width * u * focus_dist;
	this->vertical = 2 * half_height * v * focus_dist;
	this->lower_left_corner = origin - this->horizontal/2.0f - this->vertical/2.0f - w * focus_dist;
}


Ray Camera::getRay(float s, float t) {
	glm::vec3 rd = this->lens_radius * random_in_unit_disk();
	glm::vec3 offset = this->u * rd.x + this->v * rd.y;
	return Ray(this->origin + offset, this->lower_left_corner + s * this->horizontal + t * this->vertical - this->origin - offset);
}