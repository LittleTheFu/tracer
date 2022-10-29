#ifndef _C_BALL_H_
#define _C_BALL_H_

#include "geometry.h"

class CBall : public Geometry
{
public:
    virtual bool hit(const Ray &ray, HitRecord &record) const;
};

#endif