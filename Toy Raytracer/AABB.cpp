#include "AABB.h"
#include <algorithm>

bool AABB::legacy_hit(Ray& r, float t_min, float t_max) const{
	for (int dimension = 0; dimension < 3; dimension++) {
		float t0 = ffmin((min[dimension] - r.getOrigin()[dimension]) / r.getDirection()[dimension],
			(max[dimension] - r.getOrigin()[dimension]) / r.getDirection()[dimension]);
		float t1 = ffmax((min[dimension] - r.getOrigin()[dimension]) / r.getDirection()[dimension],
			(max[dimension] - r.getOrigin()[dimension]) / r.getDirection()[dimension]);

		t_min = ffmax(t0, t_min);
		t_max = ffmax(t1, t_max);
		if (t_max <= t_min)
			return false;
	}
	return true;
}

bool AABB::hit(Ray& r, float t_min, float t_max) const {
	for (int dim = 0; dim < 3; dim++) {
		float invD = 1.0f / (r.getDirection()[dim]);
		float t0 = (min[dim] - r.getOrigin()[dim]) * invD;
		float t1 = (max[dim] - r.getOrigin()[dim]) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
			return false;
	}
	return true;
}