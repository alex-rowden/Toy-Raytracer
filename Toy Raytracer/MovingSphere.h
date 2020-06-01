#pragma once
#include "Object.h"
class MovingSphere :
	public Object
{
public:
    float radius;
    glm::vec3 center_start, center_end;
    float time_start, time_end;
    MovingSphere() {}
    MovingSphere(glm::vec3 center_start_, glm::vec3 center_end_, float time_start_, float time_end_, float radius_, Material* mat) : center_start(center_start_), center_end(center_end_), time_start(time_start_), time_end(time_end_), radius(radius_) { material = mat; }
    virtual bool hit(Ray& r, float tmin, float tmax, hit_record& rec) const;
    virtual bool bounding_box(float time_start, float time_end, AABB& box) const;

    glm::vec3 getCenter(float t) const{ return center_start + ((t - time_start) / (time_end - time_start)) * (center_end - center_start); }
};

