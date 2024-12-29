#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "ball.h"
#include "ray.h"
#include "tagDef.h"
#include "transform.h"
#include "vector.h"

class Geometry;

class Light
{
public:
    Light(const Vector3 &position, float r);

    void applyTransform(const Transform &t);
    Vector3 sample(const Vector3 &thatPoint, float &pdf) const;
    Vector3 getSurfacePoint(const Vector3 &thatPoint) const;
    Vector3 getNormal(const Vector3 point) const;
    Vector3 getCenter() const;

    void setIntensity(float intensity);
    
    bool hit(const Ray &ray, float &t, Vector3 &normal, float &dot) const;
    void setTag(Tag tag);

    const Geometry *getGeometry() const;

    bool isIn(const Vector3 &point) const;
    Color getColor() const;

private:
    Ball *m_pBall;
    float m_intensity;
};

#endif