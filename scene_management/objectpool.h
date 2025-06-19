#ifndef _OBJECT_POOL_H_
#define _OBJECT_POOL_H_

#include <memory>
#include <vector>

#include "color.h"
#include "geometry.h"
#include "hitterInterface.h"
#include "ray.h"
#include "transform.h"
#include "interaction.h"
#include "primitive.h"

class ObjectPool
{
//-------for refactory----
public:
    void addPrimitive(std::shared_ptr<Primitive> primitive);
    void addPrimitives(std::vector<std::shared_ptr<Primitive>> primitives);

    void addLight(std::shared_ptr<AreaLight> light);
    const std::vector<std::shared_ptr<AreaLight>>& getLights() const;

public:
    std::vector<std::shared_ptr<AreaLight>> lights_;

private:
    std::vector<std::shared_ptr<Primitive>> primitives_;
//-----end----------------

public:
    ObjectPool(bool useBVH);

    void initHitter();

    void log();

    // void add(std::vector<std::shared_ptr<Geometry>> objects);
    // void add(std::shared_ptr<Geometry> pGeometry);
    // void add(std::shared_ptr<Light> pLight);

    void applyTransfrom(Transform t);
    void buildBoundBox();

    bool hitScene(const Ray &ray, Interaction &interaction) const;
    
public:
    Color getColorFromLight(const Ray &ray, int index) const;

    std::vector<std::shared_ptr<Primitive>> getPrimitives() const;

    // bool validBVH() const;

private:
    HitterInterface *m_pHitter;
};



#endif