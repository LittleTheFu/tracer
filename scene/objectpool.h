#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <vector>
#include "ray.h"
#include "geometry.h"
#include "hitrecord.h"
#include "color.h"
#include "light.h"
#include "transform.h"
#include "hitterInterface.h"

class ObjectPool
{
public:
    ObjectPool();

    void initHitter();

    void log();

    void add(std::vector<Geometry*> objects);
    void add(Geometry *pGeometry);
    void add(Light *pLight);

    void applyTransfrom(Transform t);
    void buildBoundBox();

    bool hitScene(const Ray &ray, HitRecord &record) const;
    
public:
    Color getColorFromLight(const Ray &ray) const;

    std::vector<Geometry *> getObjects() const;

    bool validBVH() const;

    Light *m_pLight;

private:
    std::vector<Geometry *> m_objects;
    HitterInterface *m_pHitter;
};

#endif