#pragma once
#include "Ray.h"
#include "AABB.h"
#include <glm.hpp>

class Material;


struct hit_record {
	float t;
	glm::vec3 position;
	glm::vec3 normal;
	Material* mat_ptr;
};

class Object
{
public:
	virtual bool hit(Ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float time_start, float time_end, AABB& box) const = 0;

	Material* material;
};

