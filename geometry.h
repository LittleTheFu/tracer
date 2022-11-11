#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "ray.h"
#include "hitrecord.h"
#include "vector.h"
#include "transform.h"

class Geometry
{
public:
    void init(const Vector3 &rotate, const Vector3 &position);
    void setPosition(const Vector3 &position);
    virtual bool hit(const Ray &ray, HitRecord &record) const = 0;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf) const;

    void applyTransform(const Transform &t);

    void setTag(int tag);
    int getTag() const;

private:
    virtual Vector3 dpdu(const Vector3 &point) const = 0;
    virtual Vector3 dpdv(const Vector3 &point) const = 0;

protected:
    Transform m_transform;
    int m_tag;
};

#endif