#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ray.h"
#include "geometry.h"
#include "hitrecord.h"
#include "color.h"
#include "light.h"

class ObjectPool
{
public:
    ObjectPool();

    void add(const Geometry *pGeometry);
    void add(const Light *pLight);

    bool hitScene(const Ray &ray, HitRecord &record) const;

    Color trace(const Ray &ray, int bounceNum, const HitRecord &currentState) const;
    Color getColorFromLight(const Ray &ray) const;

private:
    std::vector<const Geometry *> m_objects;
    const Light *m_pLight;

    float m_attenuation;
};

#endif