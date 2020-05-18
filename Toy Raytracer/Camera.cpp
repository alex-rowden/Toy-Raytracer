#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect) {
	glm::vec3 u, v, w;
	float theta = fov * M_PI / 180.0f;
	float half_height = tan(theta/ 2.0f);
	float half_width = aspect * half_height;
	origin = position;
	w = glm::normalize(position - lookat);
	u = glm::normalize(glm::cross(up, w));
	v = glm::normalize(glm::cross(w, u));
	//lower_left_corner = glm::vec3(-half_width, -half_height, -1.0);
	lower_left_corner = origin - half_width * u - half_height * v - w;
	horizontal = 2 * half_width * u;
	vertical = 2 * half_height * v;
}