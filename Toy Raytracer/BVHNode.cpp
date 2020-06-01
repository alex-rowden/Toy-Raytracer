#include "BVHNode.h"
#include <iostream>

int box_x_comparator(const void* a, const void* b) {
	AABB box_left, box_right;
	Object* ah = *(Object**)a;
	Object* bh = *(Object**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "No bounding box in BVHNode x comparator" << std::endl;
	if (box_left.getMin().x - box_right.getMin().x < 0) {
		return -1;
	}
	else {
		return 1;
	}
}int box_y_comparator(const void* a, const void* b) {
	AABB box_left, box_right;
	Object* ah = *(Object**)a;
	Object* bh = *(Object**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "No bounding box in BVHNode y comparator" << std::endl;
	if (box_left.getMin().y - box_right.getMin().y < 0) {
		return -1;
	}
	else {
		return 1;
	}
}int box_z_comparator(const void* a, const void* b) {
	AABB box_left, box_right;
	Object* ah = *(Object**)a;
	Object* bh = *(Object**)b;
	if (!ah->bounding_box(0, 0, box_left) || !bh->bounding_box(0, 0, box_right))
		std::cerr << "No bounding box in BVHNode z comparator" << std::endl;
	if (box_left.getMin().z - box_right.getMin().z < 0) {
		return -1;
	}
	else {
		return 1;
	}
}

BVHNode::BVHNode(Object** list, int n, float start_time, float end_time) {
	int axis = int(3 * rand() / (float)(RAND_MAX));
	if (axis == 0)
		qsort(list, n, sizeof(Object*), box_x_comparator);
	else if (axis == 1)
		qsort(list, n, sizeof(Object*), box_y_comparator);
	else
		qsort(list, n, sizeof(Object*), box_z_comparator);
	if (n == 1) {
		left = list[0];
		right = list[0];
	}
	else if (n == 2) {
		left = list[0];
		right = list[1];
	}
	else {
		left = new BVHNode(list, n / 2, start_time, end_time);
		right = new BVHNode(list + n / 2, n - n / 2, start_time, end_time);
	}
	AABB box_left, box_right;
	if (!left->bounding_box(start_time, end_time, box_left) || !right->bounding_box(start_time, end_time, box_right))
		std::cerr << "No Bounding Box in BVHNode constructor" << std::endl;
	box = AABB::surrounding_box(box_left, box_right);
}

bool BVHNode::hit(Ray& r, float t_min, float t_max, hit_record& rec) const
{
	if (box.hit(r, t_min, t_max)) {
		hit_record left_rec, right_rec;
		bool hit_left = left->hit(r, t_min, t_max, left_rec);
		bool hit_right = right->hit(r, t_min, t_max, right_rec);
		if (hit_left && hit_right) {
			if (left_rec.t < right_rec.t) {
				rec = left_rec;
			}
			else {
				rec = right_rec;
			}
			return true;
		}
		else if (hit_left) {
			rec = left_rec;
			return true;
		}
		else if (hit_right) {
			rec = right_rec;
			return true;
		}
		else {
			return false;
		}
	}
	else return false;
}

bool BVHNode::bounding_box(float time_start, float time_end, AABB& box) const
{
	box = this->box;
	return true;
}
