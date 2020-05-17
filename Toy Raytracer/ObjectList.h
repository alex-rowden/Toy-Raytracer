#pragma once
#include "Object.h"
class ObjectList : public Object
{
public:
	Object** list;
	int list_size;
	ObjectList() {}
	ObjectList(Object** l, int n) { list = l; list_size = n; }
	virtual bool hit(Ray& r, float t_min, float t_max, hit_record& rec) const;
};

