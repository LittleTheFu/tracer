#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include "geometry.h"
#include "bvhNode.h"

class BVH
{
public:
    const Light *m_pLight;

public:
    void init(const std::vector<Geometry *> objects, const Light *light);

    bool hit(BVHNode *node, const Ray &ray, HitRecord &record) const;
    bool hitSceneWithLight(const Ray &ray, HitRecord &record, bool &out_isLightHit) const;
    Color getColorFromLight(const Ray &ray) const;

private:
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

private:
    std::vector<Geometry *> m_objects;

    BVHNode *m_rootNode;
};

#endif