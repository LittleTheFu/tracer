#include "bvhNode.h"

BVHNode::BVHNode()
{
    leftChild = nullptr;
    rightChild = nullptr;

    // geometry = nullptr;
}

void BVHNode::print(const std::string &prefix) const
{
    std::string l = leftChild ? " L " : " N ";
    std::string r = rightChild ? " R " : " N ";
    int num = objects.size();
    
    std::cout << prefix << "|" << l << r << num << std::endl;
}

bool BVHNode::isLeaf() const
{
    return !leftChild && !rightChild;
}