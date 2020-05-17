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