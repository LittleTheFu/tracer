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
    std::size_t num = getSize();

    bool isLargeLeaf = num > 20;

    if(isLeaf() && isLargeLeaf)
    {
        std::cout << prefix << "|" << l << r << num << std::endl;
    }
}

bool BVHNode::isLeaf() const
{
    return !leftChild && !rightChild;
}

std::size_t BVHNode::getSize() const
{
    if (isLeaf())
        return primitives.size();

    std::size_t leftNum = 0;
    if (leftChild)
        leftNum = leftChild->getSize();

    std::size_t rightNum = 0;
    if (rightChild)
        rightNum = rightChild->getSize();

    return leftNum + rightNum;
}
