#pragma once
#include "Object.h"
#include "AABB.h"
class BVHNode :
	public Object
{
public:
	Object* left;
	Object* right;
	AABB box;
	BVHNode() {};
	BVHNode(Object** list, int n, float start_time, float end_time);

	virtual bool hit(Ray&r, float t_min, float t_max, hit_record&rec) const;
	virtual bool bounding_box(float time_start, float time_end, AABB&box) const;
};

