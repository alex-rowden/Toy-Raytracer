#include "MovingSphere.h"

bool MovingSphere::hit(Ray& r, float t_min, float t_max, hit_record& rec) const {
	glm::vec3 center = getCenter(r.getTime());
	glm::vec3 origin_center = r.getOrigin() - center;
	float ray_length = glm::dot(r.getDirection(), r.getDirection());
	float b = 2.0 * dot(origin_center, r.getDirection());
	float c = dot(origin_center, origin_center) - (radius * radius);
	float discriminant = (b * b) - (4 * ray_length * c);
	if (discriminant < 0)
		return false;
	else {
		float temp = (-b - sqrt(discriminant)) / (2 * ray_length);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.position = r.getPositionAlongRay(rec.t);
			rec.normal = (rec.position - center) / radius;
			rec.mat_ptr = material;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / (2 * ray_length);
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.position = r.getPositionAlongRay(rec.t);
			rec.normal = (rec.position - center) / radius;
			rec.mat_ptr = material;
			return true;
		}
		return false;
	}
}

bool MovingSphere::bounding_box(float time_start, float time_end, AABB& box) const {
	AABB box_start = AABB(center_start - glm::vec3(radius), center_start + radius);
	AABB box_end = AABB(center_end - glm::vec3(radius), center_end + radius);
	box = AABB::surrounding_box(box_start, box_end);
}