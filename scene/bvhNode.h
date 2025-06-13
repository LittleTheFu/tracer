#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include <memory>
#include <vector>

#include "geometry.h"
#include "primitive.h"

class BVHNode
{
public:
    BVHNode();

    void print(const std::string &prefix) const;
    bool isLeaf() const;

    std::size_t getSize() const;
    
public:
    BoundBox boundBox;

    std::shared_ptr<BVHNode> leftChild;
    std::shared_ptr<BVHNode> rightChild;

    std::vector<std::shared_ptr<Geometry>> objects;
    std::vector<std::shared_ptr<Primitive>> primitives;

    // Geometry *geometry;
};

#endif