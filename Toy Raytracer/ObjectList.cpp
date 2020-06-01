#include "ObjectList.h"

bool ObjectList::hit(Ray& r, float t_min, float t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_found = false;
	double closest = t_max;
	for (int i = 0; i < list_size; i++) {
		if (list[i]->hit(r, t_min, closest, temp_rec)) {
			hit_found = true;
			closest = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_found;
}

bool ObjectList::bounding_box(float start_time, float end_time, AABB& box) const {
	if (list_size < 1) return false;
	AABB temp_box;
	bool first_true = list[0]->bounding_box(start_time, end_time, temp_box);
	if (!first_true)
		return false;
	else
	{
		box = temp_box;
	}
	for (int i = 1; i < list_size; i++) {
		if (list[i]->bounding_box(start_time, end_time, temp_box)) {
			box = AABB::surrounding_box(box, temp_box);
		}
		else {
			return false;
		}
	}
	return true;
}