#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "ray.h"
#include "hitrecord.h"

class Geometry
{
public:
    virtual bool hit(const Ray &ray, HitRecord &record) const = 0;
};

#endif