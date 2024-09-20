#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ray.h"
#include "geometry.h"
#include "hitrecord.h"
#include "color.h"
#include "light.h"
#include "transform.h"
#include "mist.h"

class ObjectPool
{
public:
    ObjectPool();

    void add(Geometry *pGeometry);
    void add(Light *pLight);
    void add(Mist *pMist);

    void applyTransfrom(Transform t);

    bool hitScene(const Ray &ray, HitRecord &record, bool mist = false, Light *pLight = nullptr) const;
    bool hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const;

    Color trace(const Ray &ray, int bounceNum, const HitRecord &currentState) const;
    Color traceRandom(const Ray &ray, int bounceNum, const HitRecord &currentState) const;
    Color getColorFromLight(const Ray &ray) const;

    Light *m_pLight;

private:
    std::vector<Geometry *> m_objects;
    Mist *m_pMist;
};

#endif