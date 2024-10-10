#ifndef _BVH_H_
#define _BVH_H_

#include <vector>
#include "geometry.h"
#include "bvhNode.h"

class BVH
{
public:
    void init(const std::vector<Geometry *> objects);

private:
    void build();
    void generateTree();

private:
    std::vector<Geometry *> m_objects;

    BVHNode *m_rootNode;
};

#endif