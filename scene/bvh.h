#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include "geometry.h"
#include "bvhNode.h"
#include "hitterInterface.h"

class BVH : public HitterInterface
{
public:
    virtual void init(const std::vector<Geometry *> &objects, const Light *light) override;

    virtual bool hitGeometryObjectOnly(const Ray &ray, HitRecord &record) const override;
    virtual bool hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const override;
    virtual Color getColorFromLight(const Ray &ray) const override;

private:
    bool _hitGeometryObjectOnly(BVHNode *node, const Ray &ray, HitRecord &record) const;

    void build();

    BVHNode *generateTree(const std::vector<Geometry *> &objects, int depth);
    void printNode(BVHNode *node, const std::string &prefix);

    bool hitLeaf(const Ray &ray, const std::vector<Geometry *> objects, HitRecord &record) const;

    BoundBox getBoundBox(const std::vector<Geometry*> &objects) const;
    BoundBox getCentroidBox(const std::vector<Geometry*> &objects) const;

    void splitObjects(const std::vector<Geometry *> &objects,
                      const BoundBox &leftBox,
                      const BoundBox &rightBox,
                      std::vector<Geometry *> &outLeftObjects,
                      std::vector<Geometry *> &outRightObjects) const;

    void calcBestSplit(const std::vector<Geometry *> &objects) const;

private:
    BVHNode *m_rootNode;
};

#endif