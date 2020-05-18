#pragma once
#include <glm.hpp>
#include "Ray.h"

#define M_PI 3.1415926535897932384626433

class Camera
{
public:
	glm::vec3 origin, lower_left_corner, horizontal, vertical;
	Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect);
	Camera(float fov, float aspect) { Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), fov, aspect); };
	Camera() { Camera(60.0f, 2); };
	Ray getRay(float u, float v){
		return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); 
	}
};

