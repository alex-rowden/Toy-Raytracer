#pragma once
#include "Object.h"
class Sphere : public Object
{
public:
    float radius;
    glm::vec3 center;
    Sphere() {}
    Sphere(glm::vec3 center_, float radius_, Material* mat) : center(center_), radius(radius_) { material = mat; }
    virtual bool hit(Ray& r, float tmin, float tmax, hit_record& rec) const;
};

