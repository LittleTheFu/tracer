#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "geometry.h"
#include "ray.h"
#include "vector.h"
#include "transform.h"

class Light
{
public:
    Light(const Vector3 &position);

    void applyTransform(const Transform &t);
    Vector3 sample(const Vector3 &thatPoint, float &pdf) const;
    bool hit(const Ray &ray, float &t, Vector3 &normal, float &dot) const;
    void setTag(int tag);

    const Geometry *getGeometry() const;

private:
    Geometry *m_pGeometry;
};

#endif