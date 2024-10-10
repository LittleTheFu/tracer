#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include "geometry.h"

class BVHNode
{
public:
    BVHNode *leftChild;
    BVHNode *rightChild;

    Geometry *geometry;
};

#endif