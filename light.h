#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "geometry.h"
#include "ray.h"
#include "vector.h"

class Light
{
public:
    Light(const Vector3 &position);

    void setPosition(const Vector3 &position);
    bool hit(const Ray &ray, float &t, Vector3 &normal, float &dot) const;

    Geometry *m_pGeometry;
};

#endif