#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <memory>
#include <vector>

#include "color.h"
#include "geometry.h"
#include "hitrecord.h"
#include "hitterInterface.h"
#include "light.h"
#include "ray.h"
#include "transform.h"

class ObjectPool
{
public:
    ObjectPool(bool useBVH);

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