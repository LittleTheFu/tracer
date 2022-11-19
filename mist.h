#ifndef _MIST_H_
#define _MIST_H_

#include "geometry.h"

class Mist
{
public:
    bool hit(const Ray &ray, HitRecord &record) const;

private:
    Geometry *m_pGeometry;
};

#endif