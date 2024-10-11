#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include "geometry.h"
#include <vector>

class BVHNode
{
public:
    BVHNode();

    void print(const std::string &prefix) const;
    
public:
    BVHNode *leftChild;
    BVHNode *rightChild;

    std::vector<Geometry*> m_objects;

    // Geometry *geometry;
};

#endif