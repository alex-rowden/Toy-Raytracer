#pragma once
#include <glm.hpp>
#include "Ray.h"

#define M_PI 3.1415926535897932384626433

class Camera
{
private:
	float time_start, time_end;
public:
	glm::vec3 origin, lower_left_corner, horizontal, vertical;
	glm::vec3 u, v, w;
	float lens_radius = 0;
	Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect, float aperature, float focus_dist, float time_start, float time_end);
	Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect, float aperature, float focus_dist) :Camera(position, lookat, up, fov, aspect, aperature, focus_dist, 0, 0) {};
	Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 up, float fov, float aspect) :Camera(position, lookat, up, fov, aspect, 0, 1) {};
	Camera(float fov, float aspect) : Camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), fov, aspect) {}
	Camera() : Camera(60.0f, 2) {}
	Ray getRay(float u, float v);
	float uniform01();
	glm::vec3 random_in_unit_disk();
};

