#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "ray.h"
#include "hitrecord.h"
#include "vector.h"
#include "transform.h"
#include "light.h"

class Light;

class Geometry
{
public:
    Geometry();
    
    void init(const Vector3 &rotate, const Vector3 &position);
    void setPosition(const Vector3 &position);
    virtual bool hit(const Ray &ray, HitRecord &record, Light *pLight) const = 0;
    virtual Vector3 sampleFromPoint(const Vector3 &thatPoint, float &pdf) const;
    virtual Color get_f(const Vector3 &wo, const Vector3 &wi, const Vector3 &point, const Vector3 &normal) const;

    void applyTransform(const Transform &t);
    void setTransform(const Transform &t);
    Transform getTransform() const;

    void setMaterial(const Material *pMtrl);

    void setTag(int tag);
    int getTag() const;

private:
    virtual Vector3 dpdu(const Vector3 &point) const = 0;
    virtual Vector3 dpdv(const Vector3 &point) const = 0;

    virtual float u(const Vector3 &point) const = 0;
    virtual float v(const Vector3 &point) const = 0;

protected:
    Transform m_transform;
    int m_tag;

    const Material *m_pMtrl;
};

#endif