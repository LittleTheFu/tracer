#ifndef _C_PLANE_H_
#define _C_PLANE_H_

#include "geometry.h"

class CPlane : public Geometry
{
public:
    virtual bool hit(const Ray &ray, HitRecord &record) const;
};

#endif