#pragma once
#include <glm.hpp>
#include "Ray.h"
#include "Object.h"
class Material
{
public:
	virtual bool scatter(Ray&r, hit_record rec, glm::vec3&attenuation, Ray&scattered)  = 0;
};

