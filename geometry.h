#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "ray.h"

class Geometry
{
public:
    virtual bool hit(const Ray& ray) const = 0;
};

#endif