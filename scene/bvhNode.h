#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include "geometry.h"
#include <vector>

class BVHNode
{
public:
    BVHNode();

    void print(const std::string &prefix) const;
    bool isLeaf() const;

    std::size_t getSize() const;
    
public:
    BoundBox boundBox;

    BVHNode *leftChild;
    BVHNode *rightChild;

    std::vector<Geometry*> objects;

    // Geometry *geometry;
};

#endif