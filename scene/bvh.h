#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include "geometry.h"
#include "bvhNode.h"

class BVH
{
public:
    void init(const std::vector<Geometry *> objects, const Light *light);
    const Light *m_pLight;

    void build();
    BVHNode *generateTree(const std::vector<Geometry *> &objects, int depth);

    void printNode(BVHNode *node, const std::string &prefix);
    bool hit(BVHNode *node,
             const Ray &ray,
             HitRecord &record) const;

    bool hitSceneWithLight(const Ray &ray,
                           HitRecord &record,
                           bool &out_isLightHit) const;

    bool hitLeaf(const Ray &ray,
                 const std::vector<Geometry *> objects,
                 HitRecord &record) const;

    Color getColorFromLight(const Ray &ray) const;

private:
    std::vector<Geometry *> m_objects;

    BVHNode *m_rootNode;
};

#endif