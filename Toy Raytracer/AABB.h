#pragma once
#include "Ray.h"
inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class AABB
{
private:
	glm::vec3 min, max;
public:
	AABB() {};
	AABB(const glm::vec3& a, const glm::vec3& b) { min = a; max = b; }
	glm::vec3 getMin() { return min; }
	glm::vec3 getMax() { return max; }
	bool hit(Ray& r, float tmin, float tmax) const;
	bool legacy_hit(Ray& r, float tmin, float tmax) const;

	static AABB surrounding_box(AABB box0, AABB box1) {
		glm::vec3 small(
			fmin(box0.getMin().x, box1.getMin().x),
			fmin(box0.getMin().y, box1.getMin().y),
			fmin(box0.getMin().z, box1.getMin().z));
		glm::vec3 big(
			fmax(box0.getMax().x, box1.getMax().x),
			fmax(box0.getMax().y, box1.getMax().y),
			fmax(box0.getMax().z, box1.getMax().z));
		return AABB(small, big);
	}
};

