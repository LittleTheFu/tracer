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

    bool hitScene(const Ray &ray, HitRecord &record);

    Color trace(const Ray &ray, int bounceNum, const HitRecord &currentState);
    Color getColorFromLight(const Ray &ray);

private:
    std::vector<const Geometry *> m_objects;
    const Light *m_pLight;

    float m_attenuation;
};

#endif