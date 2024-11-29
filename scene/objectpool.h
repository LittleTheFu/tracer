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
#include <memory>

class ObjectPool
{
public:
    ObjectPool();

    void initHitter();

    void log();

    void add(std::vector<std::shared_ptr<Geometry>> objects);
    void add(std::shared_ptr<Geometry> pGeometry);
    void add(std::shared_ptr<Light> pLight);

    void applyTransfrom(Transform t);
    void buildBoundBox();

    bool hitScene(const Ray &ray, HitRecord &record) const;
    
public:
    Color getColorFromLight(const Ray &ray) const;

    std::vector<std::shared_ptr<Geometry>> getObjects() const;

    bool validBVH() const;

    std::shared_ptr<Light> m_pLight;

private:
    std::vector<std::shared_ptr<Geometry>> m_objects;
    HitterInterface *m_pHitter;
};

#endif